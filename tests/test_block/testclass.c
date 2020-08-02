#include "testclass.h"
#include "testclass-private.h"

/**
 * CFWObject interface
 */
static bool ctor(void* self, va_list args) 
{ 
    Script* this = self;
    this->value = va_arg(args, char*);
    return true; 
}
static bool equal(void* ptr1, void* ptr2) { return ptr1 == ptr2; }
static uint32_t hash(void* self) { return (uint32_t)self; }
static void* copy(void* self) { return NULL; }
static void dtor(void* self)
{
    // Script* this = self;
    // printf("Script::dtor %s\n", this->value);
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

ScriptValue get_Value(Script* this)
{
    return (ScriptValue)Block_copy(^() {
        return this->value;

    });
    
}