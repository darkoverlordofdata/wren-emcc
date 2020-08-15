#include "script.h"
#include "method.h"
#include <Block.h>
#include <cfw.h>
#include <stdio.h>
#include <string.h>
#include <wren.h>

typedef struct WCMethod WCMethod;

struct WCMethod {
    CFWObject obj;
    const char* module;
    const char* variable;
    const char* signature;
    WCScript* script;
    WrenHandle* handle;
    WrenHandle* method;
};

/**
 * Call a script method
 * 
 * @param this instance
 * @param name module name
 * @param name variable name
 * @param name method signature
 * @returns an object that wraps the method
 */
static bool ctor(void* self, va_list args)
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

static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self)
{
    WCMethod* this = self;
    wrenReleaseHandle(this->script->vm, this->handle);
    wrenReleaseHandle(this->script->vm, this->method);
    this->script = NULL;
    free(this->module);
    free(this->variable);
    free(this->signature);
}

const static CFWClass class = {
    .name = "WCMethod",
    .size = sizeof(WCMethod),
    .ctor = ctor,
    .dtor = dtor,
    .equal = equal,
    .hash = hash,
    .copy = copy,
};

const CFWClass* wc_method = &class;

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
    var t = wrenGetSlotType(this->script->vm, 0);
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
    var t = wrenGetSlotType(this->script->vm, 0);
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
    var t = wrenGetSlotType(this->script->vm, 0);
    if (t != WREN_TYPE_BOOL) {
        wrenSetSlotString(this->script->vm, 0, "Invalid Boolean Value");
        wrenAbortFiber(this->script->vm, 0);
        return false;
    }
    bool value = wrenGetSlotBool(this->script->vm, 0);
    return value;
}
