#include <stdio.h>
// #include <tglm/tglm.h>
#include <wren.h>
#include <cfw.h>
#include "script.h"
#include "builtins.h"

int main(int argc, char* argv[])
{

    CFWRefPool *pool = cfw_new(cfw_refpool);

    switch (ExecuteModule(NewScript((void*)&builtIns), "main")) {
    case ResultSuccess:
        fputs("wrenInterpret(): ", stdout);
        fputs("Ok\n", stdout);
        break;
    case ResultCompileError:
        fputs("wrenInterpret(): ", stdout);
        fputs("compile error\n", stdout);
        break;
    case ResultRuntimeError:
        fputs("wrenInterpret(): ", stdout);
        fputs("runtime error\n", stdout);
        break;
    }

    cfw_unref(pool);

    return 0;
}
