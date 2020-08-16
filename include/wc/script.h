#pragma once
#include <corefw/corefw.h>
#include <wren.h>
/**
 * Bind Wren Script to native functions
 */

extern CFWClass* wc_script;
typedef struct WCScript {
    CFWObject obj;
    WrenVM* vm;
} WCScript;

typedef struct WrenMethod {
    char* name;
    void* addr;
} WrenMethod;

#define MAX_METHODS 20

typedef struct WrenScript {
    char* module;
    char* className;
    void* allocate;
    void* finalize;
    WrenMethod methods[MAX_METHODS];
} WrenScript;

typedef enum {
    ResultSuccess,
    ResultCompileError,
    ResultRuntimeError
} Result;


extern Result wc_execute_string(WCScript* this, char* name);
extern Result wc_execute_module(WCScript* this, char* name);
