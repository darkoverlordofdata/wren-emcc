#include "unit.h"
#include "cfw.h"
#include "test_block/testclass.h"

int main(int argc, char *argv[])
{
	CFWRefPool *pool = cfw_new(cfw_refpool);

    Script* s = cfw_create(ScriptClass, "Fred");

    var GetValue = (ScriptValue)get_Value(s);
    
    Describe("Curry Test", ^{

        It("Value is 'Fred'", ^{
			Expect(0 == strcmp(GetValue(), "Fred"));
        });

    });

    cfw_unref(pool);
	exit(tests.failed);

}

