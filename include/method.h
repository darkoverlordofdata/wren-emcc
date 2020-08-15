#pragma once
#include <cfw.h>
#include <wren.h>

typedef struct WCMethod WCMethod;
extern const CFWClass* wc_method;

const char* wc_method_str(WCMethod* this);
double wc_method_num(WCMethod* this);
bool wc_method_bool(WCMethod* this);
