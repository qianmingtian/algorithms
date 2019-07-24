/*
    获取本地时间戳
    秒取后20位占时间戳字段前20位，
    微秒占据20位
 */
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

//先将原字段进行左移x_left位进行截取后半段，对后半段数据进行位移到[n,m],(m > n)

void init_os_time()
{
    struct timeval init_time;
    //设置的时间有下限
    gettimeofday(&init_time,NULL);

    init_time.tv_sec = 0x1000000;
    init_time.tv_usec = 0;

    if (settimeofday(&init_time, NULL))
    {
        exit(-200);
    }
}

int main()
{

    unsigned long int t1;
    unsigned long int t2;
    unsigned long int t3;
    unsigned long int t4;

    unsigned long int i;
    int flag;

    struct timeval init_time, current_time;
    time_t t;
    t = time(&t);
    printf("Today'sdateandtime:%s\n", ctime(&t));

    gettimeofday(&current_time, NULL);
    printf("current_time sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);
    
    current_time.tv_sec = current_time.tv_sec - ((current_time.tv_sec >> 20) << 20);

    current_time.tv_usec = 3;
    // flag = settimeofday(&current_time, NULL);
    // printf("%s\n", strerror(errno)); // 间接使用strerror输出错误字符串
    // if (flag)
    // {
    //     printf("\nflag  %d\n\n", flag);
    // };

    gettimeofday(&current_time, NULL);
    printf("init_time    sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);

    i = 10000000L;
    while (i--)
        ;
    gettimeofday(&current_time, NULL);
    printf("current_time sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);

    i = 10000000L;
    t = time(&t);
    printf("Today'sdateandtime:%s\n", ctime(&t));
    while (i--)
        ;
    gettimeofday(&current_time, NULL);
    printf("current_time sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);

    t4 = 15434896067;
   printf("%lx\n", t4);
   struct timeval time_decode;

    time_decode.tv_sec = t4 >> 20;
    printf("%lx\n", time_decode.tv_sec);

    time_decode.tv_usec = (t4 << 44) >> 44;
    printf("%lx\n", time_decode.tv_usec);
    time_decode.tv_usec = t4 - ((t4 >> 20) << 20);
    printf("%lx\n", time_decode.tv_usec);
printf("--------------");
    init_os_time();
     gettimeofday(&current_time, NULL);
    printf("current_time sec %lx  %ld\n", current_time.tv_sec, current_time.tv_usec);


  



}