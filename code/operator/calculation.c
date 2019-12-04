/*
 * @Author: 千铭天
 * @Date: 2019-09-19 21:59:43
 * @LastEditors: 
 * @LastEditTime: 2019-10-18 10:29:02
 * @Description:  
 */
#include <string.h>
#include <stdio.h>

int main()
{
    // char str[10]={1,2,3,4,5,6,7,8,9,0};
    char str[13] = "abc";
    char str1[10];

    strcpy(str1, "123456789");

    strncat(str,str1,10);

    printf("str is %s\n", str);
    printf("str1 is %s", str1);
}