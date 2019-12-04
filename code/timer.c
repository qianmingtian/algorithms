/*
 * @Author: your name
 * @Date: 2019-11-06 10:55:57
 * @LastEditTime: 2019-11-06 11:06:47
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \algorithms\code\timer.c
 */
#include <stdio.h>  
#include <time.h>  
#include <stdlib.h>  
#include <signal.h>  
#include <string.h>  
#include <unistd.h>  
#include <sys/time.h>


void show_handler(int sig)
{
    printf("I got signal %d\n", sig);
    int i;
    for(i = 0; i < 5; i++) 
   {
        printf("i = %d\n", i);
        sleep(1);
    }
}
 
int main(void)
{
    int i = 0;
    struct sigaction act;
    act.sa_handler = show_handler;
    sigaddset(&act.sa_mask, SIGQUIT);         //见注(1)
    act.sa_flags = SA_SIGINFO; //见注(2)
    //act.sa_flags = 0;                      //见注(3)
 
    sigaction(SIGUSR1, &act, NULL);
    while(1) 
   {
        sleep(1);
        printf("sleeping %d\n", i);
        i++;
    }
}
