/*
 * @Author: your name
 * @Date: 2019-11-11 09:21:59
 * @LastEditTime: 2019-11-11 10:35:59
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \algorithms\code\time_interrupt.c
 */
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void dealfunction1()
{
    printf("this is 1 func");
}
void dealfunction2()
{
    printf("this is 2 func");
}

int main()
{
    __timer_t timerid;
    struct sigevent evp;

    memset(&evp, 0, sizeof(struct sigevent));

    evp.sigev_signo = SIGUSR1;
    evp.sigev_notify = SIGEV_SIGNAL;

    if(-1==timer_creat(CLOCK_REALTIME,&evp,&timerid)){
        printf("fail to creat timer");
        exit(-1);
    }

    struct sigaction act;
    
    memset(&act,0,sizeof(struct sigaction));
    act.sa_handler = dealfunction1;
    act.sa_flags = 0;

    sigemptyset(&act.sa_mask);

    if(-1==sigaction(SIGUSR1,&act,NULL)){
        printf("fail to sigaction");
        exit(-1);
    }

    struct itimerspec it;
    it.it_interval.tv_sec = 1;
    it.it_interval.tv_nsec = 0;

    it.it_value.tv_sec = 5;

    if(-1==timer_settime(&timerid,0,&it,NULL)){
        printf("fail to set timer");
        exit(-1);
    }

    while(1);

    return 0;
}