#include <stdio.h>
#include <string.h>
#include <wren.h>
#include "wc/wc.h"
#include "wc/script-private.h"

/**
 * WCMethod Type Instance data
 */
typedef struct WCMethod {
    CFWObject obj;
    char* module;
    char* variable;
    char* signature;
    WCScript* script;
    WrenHandle* handle;
    WrenHandle* method;
} WCMethod;

/**
 * CFWClass Interface
 */
static bool wc_method_ctor(void* self, va_list args);
static bool wc_method_equal(void* ptr1, void* ptr2);
static uint32_t wc_method_hash(void* self);
static void* wc_method_copy(void* self);
static void wc_method_dtor(void* self);

/**
 * WCMethod Type VTable
 */
static CFWClass class = {
    .name = "WCMethod",
    .size = sizeof(WCMethod),
    .ctor = wc_method_ctor,
    .dtor = wc_method_dtor,
    .equal = wc_method_equal,
    .hash = wc_method_hash,
    .copy = wc_method_copy,
};

CFWClass* wc_method = &class;

/**
 * WCMethod:
 * Call a script method
 * 
 * @param this instance
 * @param name module name
 * @param name variable name
 * @param name method signature
 * @returns an object that wraps the method
 */
static bool wc_method_ctor(void* self, va_list args)
{
    WCMethod* this = self;
    this->script = va_arg(args, void*);
    this->module = cfw_strdup(va_arg(args, const char*));
    this->variable = cfw_strdup(va_arg(args, const char*));
    this->signature = cfw_strdup(va_arg(args, const char*));

    wrenEnsureSlots(this->script->vm, 1);
    wrenGetVariable(this->script->vm, this->module, this->variable, 0);
    this->handle = wrenGetSlotHandle(this->script->vm, 0);
    this->method = wrenMakeCallHandle(this->script->vm, this->signature);
    return true;
}

static bool wc_method_equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t wc_method_hash(void* self) { return (uint32_t)self; }
static void* wc_method_copy(void* self) { return NULL; }

/**
 * Release resources
 * 
 * @param this instance
 */
static void wc_method_dtor(void* self)
{
    WCMethod* this = self;

    wrenReleaseHandle(this->script->vm, this->handle);
    wrenReleaseHandle(this->script->vm, this->method);
    this->script = NULL;
    free(this->module);
    free(this->variable);
    free(this->signature);
}

/**
 * Call a script method
 * 
 * @param this instance
 * @returns string result
 */
const char* wc_method_str(WCMethod* this)
{
    // call cached method
    wrenSetSlotHandle(this->script->vm, 0, this->handle);
    wrenCall(this->script->vm, this->method);
    // get return value
    int t = wrenGetSlotType(this->script->vm, 0);
    if (t != WREN_TYPE_STRING) {
        wrenSetSlotString(this->script->vm, 0, "Invalid String Value");
        wrenAbortFiber(this->script->vm, 0);
        return (const char*)0;
    }
    const char* value = wrenGetSlotString(this->script->vm, 0);
    return value;
}

/**
 * Call a script method
 * 
 * @param this instance
 * @returns number result
 */
double wc_method_num(WCMethod* this)
{
    // call cached method
    wrenSetSlotHandle(this->script->vm, 0, this->handle);
    wrenCall(this->script->vm, this->method);
    // get return value
    int t = wrenGetSlotType(this->script->vm, 0);
    if (t != WREN_TYPE_NUM) {
        wrenSetSlotString(this->script->vm, 0, "Invalid Number Value");
        wrenAbortFiber(this->script->vm, 0);
        return (double)0;
    }
    double value = wrenGetSlotDouble(this->script->vm, 0);
    return value;
}

/**
 * Call a script method
 * 
 * @param this instance
 * @returns boolean result
 */
bool wc_method_bool(WCMethod* this)
{
    // call cached method
    wrenSetSlotHandle(this->script->vm, 0, this->handle);
    wrenCall(this->script->vm, this->method);
    // get return value
    int t = wrenGetSlotType(this->script->vm, 0);
    if (t != WREN_TYPE_BOOL) {
        wrenSetSlotString(this->script->vm, 0, "Invalid Boolean Value");
        wrenAbortFiber(this->script->vm, 0);
        return false;
    }
    bool value = wrenGetSlotBool(this->script->vm, 0);
    return value;
}
