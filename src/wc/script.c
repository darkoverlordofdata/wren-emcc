#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "wc/wc.h"
#include "wc/script-private.h"

/**
 * CFWClass Interface
 */
static bool wc_script_ctor(void* self, va_list args);
static bool wc_script_equal(void* ptr1, void* ptr2);
static uint32_t wc_script_hash(void* self);
static void* wc_script_copy(void* self);
static void wc_script_dtor(void* self);
/**
 * WCScript internal interface
 */
static void wc_script_log(WrenVM* vm, const char* text);
static void wc_script_error(WrenVM* vm, WrenErrorType type, const char* module, int line, const char* message);
static const char* wc_script_resolve_module(WrenVM* vm, const char* importer, const char* name);
static char* wc_script_load_module(WrenVM* vm, const char* moduleName);
static WrenForeignClassMethods wc_script_register_foreign_class(WrenVM* vm, const char* module, const char* className);
static WrenForeignMethodFn wc_script_register_foreign_method(WrenVM* vm, const char* module, const char* className, bool isStatic, const char* signature);

/**
 * WCScript Type VTable
 */
static CFWClass class = {
    .name = "WCScript",
    .size = sizeof(WCScript),
    .ctor = wc_script_ctor,
    .dtor = wc_script_dtor,
    .equal = wc_script_equal,
    .hash = wc_script_hash,
    .copy = wc_script_copy,
};

// const 
CFWClass* wc_script = &class;

//#include <corefw/file-private.h>
struct CFWFile {
	CFWStream stream;
	int fd;
	bool at_end;
};

/**
 * Create new instance of Wren VM
 * 
 * @param this instance
 * @param bindings for built-ins
 * @returns an object that wraps the script
 */
static bool wc_script_ctor(void* self, va_list args)
{
    WCScript* this = self;
    WrenConfiguration config = {
        .reallocateFn = realloc,
        .resolveModuleFn = wc_script_resolve_module,
        .loadModuleFn = wc_script_load_module,
        .bindForeignClassFn = wc_script_register_foreign_class,
        .bindForeignMethodFn = wc_script_register_foreign_method,
        .writeFn = wc_script_log,
        .errorFn = wc_script_error,
        .initialHeapSize = 1024 * 1024 * 10,
        .minHeapSize = 1024 * 1024,
        .heapGrowthPercent = 50,
        .userData = va_arg(args, void*)
    };
    this->vm = wrenNewVM(&config);
    return true;
}
static bool wc_script_equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t wc_script_hash(void* self) { return (uint32_t)self; }
static void* wc_script_copy(void* self) { return NULL; }

/**
 * Release resources
 * 
 * @param this instance
 */
static void wc_script_dtor(void* self)
{
    WCScript* this = self;
    wrenFreeVM(this->vm);
}

//////////////////////////////////////////////////////////////
/// Public WSScript* interface
//////////////////////////////////////////////////////////////

/**
 * Execute a string of script
 * 
 * @param this instance
 * @param code string of script
 */
WCSResult wc_execute_string(WCScript* this, char* code)
{
    switch (wrenInterpret(this->vm, "main", code)) {
    case WREN_RESULT_COMPILE_ERROR:
        return WCSResultCompileError;
    case WREN_RESULT_RUNTIME_ERROR:
        return WCSResultRuntimeError;
    case WREN_RESULT_SUCCESS:
        return WCSResultSuccess;
    }
}

/**
 * Load and execute a script module
 * 
 * @param this instance
 * @param name module name
 */
WCSResult wc_execute_module(WCScript* this, char* name)
{
    const char* code = wc_script_load_module(this->vm, name);
    switch (wrenInterpret(this->vm, name, code)) {
    case WREN_RESULT_COMPILE_ERROR:
        return WCSResultCompileError;
    case WREN_RESULT_RUNTIME_ERROR:
        return WCSResultRuntimeError;
    case WREN_RESULT_SUCCESS:
        return WCSResultSuccess;
    }
}

//////////////////////////////////////////////////////////////
/// WrenVM overrides
//////////////////////////////////////////////////////////////

/**
 * wc_script_resolve_module
 * 
 * Resolve the module path 
 * @param vm
 * @param importer
 * @param name
 * @returns resolved name
 */
static const char* wc_script_resolve_module(WrenVM* vm,
    const char* importer,
    const char* name)
{
    return name;
}
/**
 * wc_script_log
 * 
 * Log message
 * @param vm
 * @param text to print
 * @returns none
 */
static void wc_script_log(WrenVM* vm,
    const char* text)
{
    fputs(text, stdout);
}

/**
 * ReadTextFile
 * 
 * @param path path to file
 * @returns string with file contents
 * 
 */
static CFWString* read_text_file(char* path)
{
    struct stat statbuf;

    CFWFile* handle = cfw_new(cfw_file, path, "r");
    if (!handle) {
        printf("Unable to open %s\n", path);
        return cfw_create(cfw_string, "");
    }

    if (fstat(handle->fd, &statbuf) == -1) {
        printf("Unable to stat %s\n", path);
        return cfw_create(cfw_string, "");
    }
    
    long len = statbuf.st_size;
    char* content = (char*)calloc(1, len + 1);
    cfw_stream_read(handle, content, len);
    cfw_stream_close(handle);
    CFWString* result = cfw_create(cfw_string, content);
    free(content);
    return result;
}

/**
 * wc_script_load_module
 * 
 * Load the module from the file system
 * @param vm
 * @param module name
 * @returns loaded module as string
 */
static char* wc_script_load_module(WrenVM* vm,
    const char* moduleName)
{
    CFWString* path = cfw_create(cfw_string, "data/wren/");
    cfw_string_append_c(path, moduleName);
    cfw_string_append_c(path, ".wren");
    
    CFWString* source = read_text_file(cfw_string_c(path));
    char* result = cfw_strdup(cfw_string_c(source));
    cfw_unref(source);
    return result;
}

/**
 * wc_script_error
 * 
 * @param vm
 * @param type of error
 * @param module
 * @param line
 * @param message
 * @returns none
 * Display Wren Error
 */
static void wc_script_error(WrenVM* vm,
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
 * wc_script_register_foreign_class
 * 
 * Bind a module / class
 * @param module
 * @param className
 * @returns array of methods
 */
static WrenForeignClassMethods wc_script_register_foreign_class(WrenVM* vm,
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
 * wc_script_register_foreign_method
 * 
 * Bind method
 * @param module
 * @param className
 * @param isStatic
 * @param signature
 * @returns address of method
 */
static WrenForeignMethodFn wc_script_register_foreign_method(WrenVM* vm,
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
