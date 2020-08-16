#include <stdio.h>
#include <wren.h>
#include <corefw/corefw.h>
#include "wc/wc.h"

int main(int argc, char* argv[])
{
    CFWRefPool *pool = cfw_new(cfw_refpool);

    switch (wc_execute_module(cfw_create(wc_script, &builtIns), "main")) {
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
