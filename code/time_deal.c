#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/timeb.h>

int main(void)
{
    long i = 10000000L;
    clock_t start, finish;
    double duration;
    /* 测量一个事件持续的时间*/

    // struct timev&tval tv_start, tv_end;
    // gettimeofday(&tv_start, NULL);
    printf("Time to do %ld empty loops is \n", i);

    //  printf("GetTickCount() : %d\n", GetTickCount());

    struct timeb time_b;


    ftime(&time_b);
    start = clock();
    printf("struct timeb_time : %d\n", time_b.time);
    printf("struct timeb_millitm : %u\n", time_b.millitm);

    while (i--)
        ;
    ftime(&time_b);
    finish = clock();
    printf("struct timeb_time : %d\n", time_b.time);
    printf("struct timeb_millitm : %u\n", time_b.millitm);

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("%f seconds\n", duration);
    // gettimeofday(&tv_end, NULL);
    // printf("GetTickCount() : %d\n", GetTickCount());

    system("pause");
}