#pragma once
// #include <cfw.h>
#include <wren.h>

extern CFWClass* wc_method;

typedef struct WCMethod WCMethod;

// public methods
const char* wc_method_str(WCMethod* this);
double wc_method_num(WCMethod* this);
bool wc_method_bool(WCMethod* this);


