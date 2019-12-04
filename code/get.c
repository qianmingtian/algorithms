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
#define set_bits(x, x_left, n, m) ((x << x_left) & \
                                   ~(~0L << (m - n + 1)) << (n - 1))


void init_os_time()
{
    struct timeval init_time;
    //设置的时间有下限
    gettimeofday(&init_time, NULL);

    init_time.tv_sec = 0x1000000;
    init_time.tv_usec = 0;

    if (settimeofday(&init_time, NULL))
    {
        exit(-200);
    }
}

unsigned long long int getlocaltime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("tv sec %llx  %llx\n", tv.tv_sec, tv.tv_usec);
    /*
    64bits:  tv 1563954740  109900   t1 = 80e341ad4c  
    32bits:  tv 1563954740  109900   t1 = e341ad4c  
    */
    unsigned long long int tv_sec_tmp = tv.tv_sec;
    tv_sec_tmp = (tv_sec_tmp - ((tv_sec_tmp >> 20) << 20)) << 20;
    printf("tem sec %llx  \n", tv_sec_tmp);
    // unsigned long long int tmp = 0L;
    // tmp = set_bits(tmp, 0, 1, 20);
    // tv_sec_tmp = set_bits(tv_sec_tmp, 20, 21, 40);
    // tv_sec_tmp = tv_sec_tmp | tmp;

    //obtain  usec
    unsigned long long int tv_usec_tmp = tv.tv_usec;
    tv_usec_tmp = set_bits(tv_usec_tmp, 0, 1, 20);
    printf("tem usec %llx  \n", tv_usec_tmp);

    //obtain time encoded
    unsigned long long int time_encode = tv_sec_tmp | tv_usec_tmp;

    printf("time_encode %llx  \n", time_encode);

    return time_encode;
}

int main()
{
    unsigned long long int time = getlocaltime();
    printf("encode time is : %llx\n", time);
}