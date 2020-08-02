#include "script.h"
#include <cfw.h>
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include <Block.h>
/**
 * WrenVM interface
 */
void VMLog(WrenVM* vm, const char* text);
void VMError(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message);
const char* VMResolveModule(WrenVM* vm, const char* importer, const char* name);
char* VMLoadModule(WrenVM* vm, const char* moduleName);
WrenForeignClassMethods VMRegisterForeignClass(WrenVM* vm, const char* module, const char* className);
WrenForeignMethodFn VMRegisterForeignMethod(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);

/**
 * CFWObject interface
 */
static bool ctor(void* self, va_list args) { return true; }
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self)
{
    Script* this = self;
    printf("BYE!!!\n");
    wrenFreeVM(this->vm);
}
const static CFWClass class = { 
    .name = "Script", 
    .size = sizeof(Script), 
    .ctor = ctor, 
    .dtor = dtor, 
    .equal = equal, 
    .hash = hash, 
    .copy = copy,
}; 

const CFWClass* ScriptClass = &class;

/**
 * Create new instance of Wren VM
 * 
 * @param this instance
 * @param builtIns foreign interface bindings
 */
void* NewScript(void* builtIns)
{
    Script* this = cfw_create((CFWClass*)ScriptClass);

    WrenConfiguration config = {
        .reallocateFn = realloc,
        .resolveModuleFn = VMResolveModule,
        .loadModuleFn = VMLoadModule,
        .bindForeignClassFn = VMRegisterForeignClass,
        .bindForeignMethodFn = VMRegisterForeignMethod,
        .writeFn = VMLog,
        .errorFn = VMError,
        .initialHeapSize = 1024 * 1024 * 10,
        .minHeapSize = 1024 * 1024,
        .heapGrowthPercent = 50,
        .userData = builtIns
    };

    this->vm = wrenNewVM(&config);
    return this;
}

/**
 * Execute a string of script
 * 
 * @param this instance
 * @param code string of script
 */
Result ExecuteString(Script* this, char* code)
{
    var res = wrenInterpret(this->vm, "main", code);
    if (res == WREN_RESULT_COMPILE_ERROR) {
        return ResultCompileError;
    }
    if (res == WREN_RESULT_RUNTIME_ERROR) {
        return ResultRuntimeError;
    }
    return ResultSuccess;
}

/**
 * Load and execute a script module
 * 
 * @param this instance
 * @param name module name
 */
Result ExecuteModule(Script* this, char* name)
{
    var code = VMLoadModule(this->vm, name);
    var res = wrenInterpret(this->vm, name, code);

    if (res == WREN_RESULT_COMPILE_ERROR) {
        return ResultCompileError;
    }
    if (res == WREN_RESULT_RUNTIME_ERROR) {
        return ResultRuntimeError;
    }
    return ResultSuccess;
}

/**
 * Call a script method
 * 
 * @param this instance
 * @param name module name
 * @param name variable name
 * @param name method signature
 * @returns a function that calls the vm returning a string
 */
void* CallMethodStr(Script* this, const char* module, const char* variable, const char* signature)
{
    wrenEnsureSlots(this->vm, 1);
    wrenGetVariable(this->vm, module, variable, 0);
    __block WrenHandle* handle = wrenGetSlotHandle(this->vm, 0); 
    __block WrenHandle* method = wrenMakeCallHandle(this->vm, signature);

    return Block_copy(^() {
        wrenSetSlotHandle(this->vm, 0, handle);
        wrenCall(this->vm, method);
        const char* value = wrenGetSlotString(this->vm, 0);
        return value;
    });
}

/**
 * Call a script method
 * 
 * @param this instance
 * @param name module name
 * @param name variable name
 * @param name method signature
 * @returns a function that calls the vm returning a double
 */
void* CallMethodDbl(Script* this, const char* module, const char* variable, const char* signature)
{
    wrenEnsureSlots(this->vm, 1);
    wrenGetVariable(this->vm, module, variable, 0);
    __block WrenHandle* handle = wrenGetSlotHandle(this->vm, 0); 
    __block WrenHandle* method = wrenMakeCallHandle(this->vm, signature);

    return Block_copy(^() {
        wrenSetSlotHandle(this->vm, 0, handle);
        wrenCall(this->vm, method);
        double value = wrenGetSlotDouble(this->vm, 0);
        return value;
    });
}

//////////////////////////////////////////////////////////////
/// WrenVM overrides
//////////////////////////////////////////////////////////////

/**
 * VMResolveModule
 * 
 * Resolve the module path 
 * @param VM
 * @param importer
 * @param name
 * @returns resolved name
 */
const char* VMResolveModule(WrenVM* vm,
    const char* importer,
    const char* name)
{
    return name;
}
/**
 * VMLog
 * 
 * Log message
 * @param VM
 * @param text to print
 * @returns none
 */
void VMLog(WrenVM* vm,
    const char* text)
{
    fputs(text, stdout);
}

/**
 * VMLoadModule
 * 
 * Load the module from the file system
 * @param VM
 * @param module name
 * @returns loaded module as string
 */
char* VMLoadModule(WrenVM* vm,
    const char* moduleName)
{
    char* path = join("data/wren/", moduleName, ".wren");
    CFWString* source = CFWFS.readTextFile((char*)path);
    char* result = cfw_strdup(cfw_string_c(source));
    free(path);
    cfw_unref(source);
    return result;
}

/**
 * VMError
 * 
 * @param VM
 * @param type of error
 * @param module
 * @param line
 * @param message
 * @returns none
 * Display Wren Error
 */
void VMError(WrenVM* vm,
    WrenErrorType type,
    const char* module,
    int line,
    const char* message)
{
    switch (type) {
    case WREN_ERROR_COMPILE:
        fprintf(stderr, "compile time error: %s:%d:%s\n", module, line, message);
        break;
    case WREN_ERROR_RUNTIME:
        fprintf(stderr, "runtime error: %s\n", message);
        break;
    case WREN_ERROR_STACK_TRACE:
        fprintf(stderr, "stack trace: %s:%d:%s\n", module, line, message);
        break;
    }
}

/**
 * VMRegisterForeignClass
 * 
 * Bind a module / class
 * @param module
 * @param className
 * @returns array of methods
 */
WrenForeignClassMethods VMRegisterForeignClass(WrenVM* vm,
    const char* module,
    const char* className)
{
    var bindings = (WrenScript*)wrenGetUserData(vm);

    WrenForeignClassMethods methods;
    methods.allocate = NULL;
    methods.finalize = NULL;

    for (var i = 0; bindings[i].module != NULL; i++) {
        if (strcmp(module, bindings[i].module) != 0)
            continue;
        if (strcmp(className, bindings[i].className) != 0)
            continue;
        methods.allocate = bindings[i].allocate;
        methods.finalize = bindings[i].finalize;
        return methods;
    }
    return methods;
}

/**
 * VMRegisterForeignMethod
 * 
 * Bind method
 * @param module
 * @param className
 * @param isStatic
 * @param signature
 * @returns address of method
 */
WrenForeignMethodFn VMRegisterForeignMethod(WrenVM* vm,
    const char* module,
    const char* className,
    bool isStatic,
    const char* signature)
{
    var bindings = (WrenScript*)wrenGetUserData(vm);

    for (var i = 0; bindings[i].module != NULL; i++) {
        if (strcmp(module, bindings[i].module) != 0)
            continue;
        if (strcmp(className, bindings[i].className) != 0)
            continue;

        for (var j = 0; bindings[i].methods[j].addr != NULL; j++) {
            bool is_static = (bindings[i].methods[j].name[0] == '+');
            if (is_static != isStatic)
                continue;
            char* name = isStatic ? bindings[i].methods[j].name + 1 : bindings[i].methods[j].name;
            if (strcmp(signature, name) != 0)
                continue;
            return bindings[i].methods[j].addr;
        }
    }
    return NULL;
}

