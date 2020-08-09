#include "cfw.h"
#include "unit.h"

int main(int argc, char* argv[])
{
    CFWRefPool* pool = cfw_new(cfw_refpool);

    var fred = new (CFWString, "Fred");

    char* str = join("this", " ", "is", " ", "a", " ", "test");

    Describe("Basic Tests", ^{
        It("string length is 14", ^{
            Expect(strlen(str) == 14);
        });

        It("value is 'this is a test'", ^{
            Expect(0 == strcmp("this is a test", str));
        });

        It("creates a string equal to 'Fred'", ^{
            Expect(0 == cfw_string_find_c(fred, "Fred", cfw_range_all));
        });
    });

    free(str);
    cfw_unref(pool);
    exit(tests.failed);
}