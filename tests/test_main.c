#include "unit.h"
#include "cfw.h"

int main(int argc, char *argv[])
{
	CFWRefPool *pool = cfw_new(cfw_refpool);

    char* str = join("this", " ", "is", " ", "a", " ", "test");

    Describe("Basic Tests", ^{

        It("string length is 14", ^{
			Expect(strlen(str) == 14);
        });

        It("value is 'this is a test'", ^{
            Expect(0 == strcmp("this is a test", str));
        });
    });

    free(str);
    cfw_unref(pool);
	exit(tests.failed);

}