#include <stdio.h>
#include <cfw.h>
#include <wren.h>
#include <Block.h>
#include "unit.h"
#include "script.h"
#include "builtins.h"

typedef const char* (^ICallStr)();
typedef double (^ICallDbl)();

int main(int argc, char *argv[])
{
	CFWRefPool *pool = cfw_new(cfw_refpool);

    var s = NewScript((void*)&builtIns);

    switch (ExecuteModule(s, "test")) {
    case ResultSuccess:
        fputs("wrenInterpret(): ", stdout);
        fputs("Ok\n", stdout);


        Describe("Basic Tests", ^{

            It("return value is 'Hola Mundo'", ^{
                ICallStr helloWorld = CallMethodStr(s, "test", "Main", "helloWorld()");
                Expect(0 == strcmp(helloWorld(), "Hola Mundo"));
            });

            It("return value is 'Hello World'", ^{
                ICallStr testly = CallMethodStr(s, "test", "test", "testly()");
                Expect(0 == strcmp(testly(), "Hello World"));
            });

            It("x is 3", ^{
                ICallDbl vectorx = CallMethodDbl(s, "test", "test", "vectorx()");
                double r1 = vectorx();
                Expect(3 == (int)r1);
            });

            It("return value is 32", ^{
                ICallDbl vectors = CallMethodDbl(s, "test", "test", "vectors()");
                double r2 = vectors();
                Expect(32 == (int)r2);
            });
            
        });
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
	exit(tests.failed);

}