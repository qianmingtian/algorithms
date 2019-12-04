/*
 * @Author: 千铭天
 * @Date: 2019-12-03 14:50:55
 * @LastEditors: 
 * @LastEditTime: 2019-12-03 15:01:26
 * @Description:  
 */
#include<stdio.h>
#include<stdlib.h>

int main()
{
    FILE *fp;
    char word[40];
    if((fp=fopen("1","a+"))==NULL)
    {
        printf("ooen error\n");
        exit(1);
    }
    while(fscanf(fp,"%x",word)==1)
    {
        puts(word);
    }

    if(fclose(fp)!=0)
        fprintf(stderr,"error cloaing file");




    printf("Hello world!");
    return 0;
}