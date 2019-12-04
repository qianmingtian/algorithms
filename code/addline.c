/*
 * @Author: your name
 * @Date: 2019-11-18 21:21:36
 * @LastEditTime: 2019-11-25 11:49:22
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \algorithms\code\addline.c
 */
#include <stdio.h>

int exter = 5;           //外部链接，可用extern引用
static int stayhere = 8; //内部链接，文件作用域，不可被extern应用

int main()
{
    int junk[3][4] = {{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 2, 3, 4}};
    int i, j;
    int x = 30;

    i = 2;
    j = 2;

    {
        i = 2;
        j = 2;
        int x = 90;
        x++;
    }
    int total = 0;
    for (i = 0; i < 3; i++)
    {
        // total = total + junk[i];
    }

    i = 2;
    j = 2;
    int arrary[i][j];
    int aarrary[2][2] = {12, 14, 16};

    int a=1 ;
    a = (0x01<<4)|a;
    
}