#include "script.h"
#include <Block.h>
#include <cfw.h>
#include <stdio.h>
#include <string.h>
#include <wren.h>
/**
 * WrenVM interface
 */
void vm_log(WrenVM* vm, const char* text);
void vm_error(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message);
const char* vm_resolve_module(WrenVM* vm, const char* importer, const char* name);
char* vm_load_module(WrenVM* vm, const char* moduleName);
WrenForeignClassMethods vm_register_foreign_class(WrenVM* vm, const char* module, const char* className);
WrenForeignMethodFn vm_register_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);

/**
 * Create new instance of Wren VM
 * 
 * @param this instance
 * @param bindings for built-ins
 */
static bool ctor(void* self, va_list args)
{
    WCScript* this = self;
    WrenConfiguration config = {
        .reallocateFn = realloc,
        .resolveModuleFn = vm_resolve_module,
        .loadModuleFn = vm_load_module,
        .bindForeignClassFn = vm_register_foreign_class,
        .bindForeignMethodFn = vm_register_foreign_method,
        .writeFn = vm_log,
        .errorFn = vm_error,
        .initialHeapSize = 1024 * 1024 * 10,
        .minHeapSize = 1024 * 1024,
        .heapGrowthPercent = 50,
        .userData = va_arg(args, void*)
    };
    this->vm = wrenNewVM(&config);
    return true;
}
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self)
{
    WCScript* this = self;
    wrenFreeVM(this->vm);
}
const static CFWClass class = {
    .name = "WCScript",
    .size = sizeof(WCScript),
    .ctor = ctor,
    .dtor = dtor,
    .equal = equal,
    .hash = hash,
    .copy = copy,
};

const CFWClass* wc_script = &class;

/**
 * Execute a string of script
 * 
 * @param this instance
 * @param code string of script
 */
Result wc_execute_string(WCScript* this, char* code)
{
    switch (wrenInterpret(this->vm, "main", code)) {
    case WREN_RESULT_COMPILE_ERROR:
        return ResultCompileError;
    case WREN_RESULT_RUNTIME_ERROR:
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
Result wc_execute_module(WCScript* this, char* name)
{
    const char* code = vm_load_module(this->vm, name);
    switch (wrenInterpret(this->vm, name, code)) {
    case WREN_RESULT_COMPILE_ERROR:
        return ResultCompileError;
    case WREN_RESULT_RUNTIME_ERROR:
        return ResultRuntimeError;
    }
    return ResultSuccess;
}

//////////////////////////////////////////////////////////////
/// WrenVM overrides
//////////////////////////////////////////////////////////////

/**
 * vm_resolve_module
 * 
 * Resolve the module path 
 * @param vm
 * @param importer
 * @param name
 * @returns resolved name
 */
const char* vm_resolve_module(WrenVM* vm,
    const char* importer,
    const char* name)
{
    return name;
}
/**
 * vm_log
 * 
 * Log message
 * @param vm
 * @param text to print
 * @returns none
 */
void vm_log(WrenVM* vm,
    const char* text)
{
    fputs(text, stdout);
}

/**
 * vm_load_module
 * 
 * Load the module from the file system
 * @param vm
 * @param module name
 * @returns loaded module as string
 */
char* vm_load_module(WrenVM* vm,
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
 * vm_error
 * 
 * @param vm
 * @param type of error
 * @param module
 * @param line
 * @param message
 * @returns none
 * Display Wren Error
 */
void vm_error(WrenVM* vm,
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
 * vm_register_foreign_class
 * 
 * Bind a module / class
 * @param module
 * @param className
 * @returns array of methods
 */
WrenForeignClassMethods vm_register_foreign_class(WrenVM* vm,
    const char* module,
    const char* className)
{
    WrenScript* bindings = (WrenScript*)wrenGetUserData(vm);

    WrenForeignClassMethods methods;
    methods.allocate = NULL;
    methods.finalize = NULL;

    for (int i = 0; bindings[i].module != NULL; i++) {
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
 * vm_register_foreign_method
 * 
 * Bind method
 * @param module
 * @param className
 * @param isStatic
 * @param signature
 * @returns address of method
 */
WrenForeignMethodFn vm_register_foreign_method(WrenVM* vm,
    const char* module,
    const char* className,
    bool isStatic,
    const char* signature)
{
    WrenScript* bindings = (WrenScript*)wrenGetUserData(vm);

    for (int i = 0; bindings[i].module != NULL; i++) {
        if (strcmp(module, bindings[i].module) != 0)
            continue;
        if (strcmp(className, bindings[i].className) != 0)
            continue;

        for (int j = 0; bindings[i].methods[j].addr != NULL; j++) {
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
