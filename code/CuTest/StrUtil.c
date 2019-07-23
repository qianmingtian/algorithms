#include <string.h>
#include <ctype.h>

#include "CuTest.h"

char* StrToUpper(char* str) {
    char* p;
    for (p = str ; *p ; ++p) *p = toupper(*p);
    return str;
}


//****************************************
/*测试用例 1：
    input：输入
    actual：函数调用执行输出
    expected: 期望输出
*/
void TestStrToUpper(CuTest *tc) {
    char* input = strdup("hello world");
    char* actual = StrToUpper(input);
    char* expected = "HeLLO WORLD";
    CuAssertStrEquals(tc, expected, actual);
}


//调用上述测试用例
CuSuite* StrUtilGetSuite() {
    CuSuite* suite = CuSuiteNew();

    /*add other test SUITE_ADD_TEST(suite, TestStrToUpper_NULL);      */
    SUITE_ADD_TEST(suite, TestStrToUpper);

    return suite;
}
