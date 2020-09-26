#pragma once
#include <corefw/corefw.h>
#include <wren.h>
// #include "script-private.h"
/**
 * Bind Wren Script to native functions
 */

extern CFWClass* wc_script;
typedef struct WCScript WCScript;
typedef struct WrenMethod WrenMethod;
typedef struct WrenScript WrenScript; 

typedef enum {
    WCSResultSuccess,
    WCSResultCompileError,
    WCSResultRuntimeError
} WCSResult;

// public methods
extern WCSResult wc_execute_string(WCScript* this, char* name);
extern WCSResult wc_execute_module(WCScript* this, char* name);
