#include <stdio.h>

#include "CuTest.h"

//调用函数声明
CuSuite* StrUtilGetSuite();
CuSuite* AddGetSuite();

void RunAllTests(void)
{
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();

	//加载调用
    CuSuiteAddSuite(suite, AddGetSuite());
    CuSuiteAddSuite(suite, StrUtilGetSuite());

	CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

int main(void)
{
	RunAllTests();
}
