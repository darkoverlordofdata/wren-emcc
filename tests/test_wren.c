#include <cfw.h>
#include <stdio.h>
#include <wren.h>
#include "builtins.h"
#include "script.h"
#include "method.h"
#include "unity/unity.h"

CFWRefPool* pool;
WCScript* script;
WCMethod* hello_world;
WCMethod* vectorx;

void setUp(void) 
{
    pool = cfw_new(cfw_refpool);
    script = cfw_create(wc_script, &builtIns);
    wc_execute_module(script, "test");
    hello_world = cfw_create(wc_method, script, "test", "Main", "helloWorld()");
    vectorx = cfw_create(wc_method, script, "test", "test", "vectorx()");
}    

void tearDown(void) 
{ 
    cfw_unref(pool);
}

void test_method_num_is_3(void)
{
    TEST_ASSERT_EQUAL_UINT32(3, wc_method_num(vectorx));
}

void test_method_str_is_hola_mundo(void)
{
    TEST_ASSERT_EQUAL_STRING("Hola Mundo", wc_method_str(hello_world));
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_method_num_is_3);
    RUN_TEST(test_method_str_is_hola_mundo);
    return UNITY_END();
}

