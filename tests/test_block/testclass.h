#pragma once
#include <stdarg.h>
#include <Block.h>
#include "cfw.h"

/**
 * Class Script
 */
extern const CFWClass* ScriptClass;
typedef struct Script Script; 
typedef char* (^ScriptValue)();


