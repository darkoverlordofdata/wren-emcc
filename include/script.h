#pragma once
#include <cfw.h>
#include <wren.h>
/**
 * Bind Wren Script to native functions
 */

typedef struct Script Script;
extern const CFWClass* ScriptClass;

/**
 * Class Script
 */

struct Script {
    CFWObject obj;
    WrenVM* vm;
};

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

extern void* NewScript(void* builtIns);
extern Result ExecuteString(Script* this, char* code);
extern Result ExecuteModule(Script* this, char* code);
extern void* CallMethodStr(Script* this, const char* module, const char* variable, const char* signature);
extern void* CallMethodDbl(Script* this, const char* module, const char* variable, const char* signature);
