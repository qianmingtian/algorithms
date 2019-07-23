#include "CuTest.h"
#include <string.h>

//功能函数
int Add(int a, int b){
    return a+b;
}

//****************************************
/*
    测试用例 1：
        input：输入
        actual：函数调用执行输出
        expected: 期望输出
*/
void TestAdd_1(CuTest *tc) {
    int input_a = 1;
    int input_b = 2;
    int actual = Add(input_a,input_b);
    int expected = 3;
    CuAssertIntEquals(tc, expected, actual);
}

//****************************************

/*
    测试用例 2：
        input：输入
        actual：函数调用执行输出
        expected: 期望输出
*/
void TestAdd_2(CuTest *tc) {
    int input_a = 3;
    int input_b = 4;
    int actual = Add(input_a,input_b);
    int expected = 3;
    CuAssertIntEquals(tc, expected, actual);
}
//调用上述测试用例
 CuSuite* AddGetSuite() {
    CuSuite* suite = CuSuiteNew();
    
    /*add other test SUITE_ADD_TEST(suite, TestStrToUpper_NULL);      */
    SUITE_ADD_TEST(suite, TestAdd_1);
    SUITE_ADD_TEST(suite, TestAdd_2);
        
    return suite;
}