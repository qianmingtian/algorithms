/*
    获取本地时间戳
    秒取后20位占时间戳字段前20位，
    微秒占据20位
 */
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

//先将原字段进行左移x_left位进行截取后半段，对后半段数据进行位移到[n,m],(m > n)
#define set_bits(x, x_left, n, m) ((x << x_left) & \
                                   ~(~0L << (m - n + 1)) << (n - 1))
unsigned long int getlocaltime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    printf("tv %ld  %ld\n", tv.tv_sec, tv.tv_usec);


    //64位os  
    //obtain  sec
    unsigned long int tv_sec_tmp = tv.tv_sec;
    tv_sec_tmp = (tv_sec_tmp - ((tv_sec_tmp >> 20)<< 20))<<20;
    // unsigned long int tmp = 0L;
    // tmp = set_bits(tmp, 0, 1, 20);
    // tv_sec_tmp = set_bits(tv_sec_tmp, 20, 21, 40);
    // tv_sec_tmp = tv_sec_tmp | tmp;

    //obtain  usec
    unsigned long int tv_usec_tmp = tv.tv_usec;
    tv_usec_tmp = set_bits(tv_usec_tmp, 0, 1, 20);

    //obtain time encoded
    unsigned long int time_encode = tv_sec_tmp | tv_usec_tmp;

    return time_encode;
}

/*对编码的时间进行解码 */
struct timeval time_tv_decode(unsigned long int time_encode)
{
    struct timeval time_decode;

    time_decode.tv_sec = time_encode >> 20;

    time_decode.tv_usec = (time_encode << 44) >> 44;

    return time_decode;
}

int correct_os_time_imprecise(struct timeval proofread_time)
{
    //由于时间戳内的时间并不是完整的系统时间，这里利用本地系统前半部分的时间进行拼接，完成粗同步
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    proofread_time.tv_sec = ((current_time.tv_sec >> 20) << 20) | proofread_time.tv_sec;

    if (settimeofday(&current_time, NULL))
    {
        printf("os time imprecise proofread_time fail ..maybe need root");
        return -214;
    }
    return 0;
}

/*校准系统时间 */
int correct_os_time_precise(unsigned long int tem_1, unsigned long int tem_2, unsigned long int tem_3, unsigned long int tem_4)
{
    struct timeval current_time;
    struct timeval t1;
    struct timeval t2;
    struct timeval t3;
    struct timeval t4;

    //转化为时间格式(timeval)
    t4 = time_tv_decode(tem_4);
    t1 = time_tv_decode(tem_1);

    t2 = time_tv_decode(tem_2);
    t3 = time_tv_decode(tem_3);

    //计算时间差
    // local_variable_information.time_difference_to_its_benchmark = (t2 - t1 + t4 - t3) / 2;
    signed long int sec, usec;
    sec = t2.tv_sec + t4.tv_sec;
    usec = t2.tv_usec + t4.tv_usec;
    while (usec > 999999)
    {
        sec++;
        usec -= 999999;
    }
    sec = sec - t1.tv_sec - t3.tv_sec;
    usec = usec - t1.tv_usec - t3.tv_usec;
    // sec = 0;
    // usec = 100000;
    while (usec < 0)
    {
        sec--;
        usec += 999999;
    }
    if (sec % 2) //奇数时,整除2为整数部分，小数部分直接加最大Usec的一半
    {
        if (sec < 0)
        {
            sec = sec / 2;
            usec = (usec / 2) - 499999;
            while (usec < 0)
            {
                sec--;
                usec += 999999;
            }
        }
        else
        {
            sec = sec / 2;
            usec = (usec / 2) + 499999;
            while (usec > 999999)
            {
                sec++;
                usec -= 999999;
            }
        }
    }
    else
    {
        sec = sec / 2;
        usec = usec / 2;
    }
    // usec = 999998;

    gettimeofday(&current_time, NULL);
    printf("current sec: %ld\n", current_time.tv_sec);
    printf("current usec: %ld\n", current_time.tv_usec);
    printf("------------------\n");
    printf("t1 sec %ld  %ld\n", t1.tv_sec, t1.tv_usec);
    printf("t2 sec %ld  %ld\n", t2.tv_sec, t2.tv_usec);
    printf("t3 sec %ld  %ld\n", t3.tv_sec, t3.tv_usec);
    printf("t4 sec %ld  %ld\n", t4.tv_sec, t4.tv_usec);
    printf("sec :%ld\n usec :%ld\n", sec, usec);
    printf("------------------\n");

    if (sec < 0)
    {
        unsigned long int tem = labs(sec);
        current_time.tv_sec -= tem;
        current_time.tv_usec += usec;

        while (current_time.tv_usec > 999999)
        {
            current_time.tv_sec++;
            current_time.tv_usec -= 999999;
        }
    }
    else
    {
        current_time.tv_sec += sec;
        current_time.tv_usec += usec;
        while (current_time.tv_usec > 999999)
        {
            current_time.tv_sec++;
            current_time.tv_usec -= 999999;
        }
    }

    printf("current sec: %ld\n", current_time.tv_sec);
    printf("current usec: %ld\n", current_time.tv_usec);

    /*
    success ： 0 ，not enter
    fail : -1, enter
    code -214 : correct time fail
     */
    if (settimeofday(&current_time, NULL))
    {
        printf("precise correct time fault,maybe need root ");
        return -214;
    }
    return 0;
}

void init_os_time()
{
    struct timeval init_time;
    init_time.tv_sec = 0;
    init_time.tv_usec = 0;

    if (settimeofday(&init_time, NULL))
    {
        exit(-200);
    }
}

int main()
{

    unsigned long int t1;
    // unsigned long int t2;
    // unsigned long int t3;
    // unsigned long int t4;

    // unsigned long int i;

    // i = 10000000L;
    t1 = getlocaltime();
    // while (i--)
    //     ;
    // i = 10000000L;
    // t2 = getlocaltime();
    // while (i--)
    //     ;
    // i = 10000000L;
    // t3 = getlocaltime();
    // while (i--)
    //     ;
    // i = 10000000L;
    // t4 = getlocaltime();
    // t4 = 15434896067;
    // t2 = 15434540034;
    // t3 = 15435583816;
    // t1 = 15434625660;
    printf("t1 = %lx\n", t1);
    // printf("t2 = %ld\n", t2);
    // printf("t3 = %ld\n", t3);
    // printf("t4 = %ld\n", t4);
    // printf("t5 = %ld\n", getlocaltime());
    // correct_os_time_precise(t1, t2, t3, t4);

    // signed long int neg = -4;
    // unsigned long int pos = 65, sum;
    // sum = pos + neg;

    // printf("sum : %ld\n", sum);

    // struct timeval init_time, current_time;
    // gettimeofday(&current_time, NULL);
    // printf("init sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);
    // init_time.tv_sec = 3;
    // init_time.tv_usec = 0;

    // if (settimeofday(&init_time, NULL))
    // {
    //     exit(-200);
    // }
    // gettimeofday(&current_time, NULL);
    // printf("init sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);
}