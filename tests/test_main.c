// #include "cfw.h"
#include <corefw/corefw.h>
#include "unity/unity.h"

CFWRefPool* pool;
CFWString* fred;
CFWString* freda;
char* str;

void setUp(void)
{
    pool = cfw_new(cfw_refpool);
    fred = cfw_create(cfw_string, "Fred");
    freda = cfw_create(cfw_string, "Fred");
    // str = join("this", " ", "is", " ", "a", " ", "test");
}

void tearDown(void)
{
    // free(str);
    cfw_unref(pool);
}

// void test_length_is_14(void)
// {
//     TEST_ASSERT_EQUAL_UINT32(14, strlen(str));
// }

// void test_is_this_is_a_test(void)
// {
//     TEST_ASSERT_EQUAL_STRING("this is a test",str);
// }

void test_is_equal_to_Fred(void)
{
    TEST_ASSERT_EQUAL_STRING("Fred", cfw_string_c(fred));
}

void test_is_equal_to_freda(void)
{
    TEST_ASSERT_EQUAL_UINT32(0, cfw_string_find(fred, freda, cfw_range_all));
}

int main(void)
{
    UNITY_BEGIN();
    // RUN_TEST(test_length_is_14);
    // RUN_TEST(test_is_this_is_a_test);
    RUN_TEST(test_is_equal_to_Fred);
    RUN_TEST(test_is_equal_to_freda);
    return UNITY_END();
}

