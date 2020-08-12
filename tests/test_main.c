#include "cfw.h"
#include "unit.h"

int main(int argc, char* argv[])
{
    CFWRefPool* pool = cfw_new(cfw_refpool);

    CFWString* fred = cfw_create(CFWStringClass, "Fred");   

    // var fred = new_(CFWString, "Fred");
    var freda = new_(CFWString, "Freda");

    char* str = join("this", " ", "is", " ", "a", " ", "test");

    Describe("Basic Tests", ^{
        It("string length is 14", ^{
            Expect(strlen(str) == 14);
        });

        It("value is 'this is a test'", ^{
            Expect(0 == strcmp("this is a test", str));
        });

        It("creates a string equal to 'Fred'", ^{
            Expect(0 == cfw_string_find_c(fred, "Fred", cfw_range(0, 4)));
            // Expect(0 == cfw_string_find_c(fred, "Fred", cfw_range_all));
        });

        It("creates a string equal to freda", ^{
            Expect(0 == cfw_string_find(fred, freda, cfw_range_all));
        });
    });

    free(str);
    cfw_unref(pool);
    exit(tests.failed);
}