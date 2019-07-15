参考网址：
1.http://bjtime.cn/info/view.asp?id=307

2.https://www.cnblogs.com/book-gary/p/3716790.html

## **获取时间可用的函数：**

4、GetLocalTime(SYSTEMTIME&) 获取本地时间，有毫秒

SetLocalTime(SYSTEMTIME&) 设置本地时间

SYSTEMTIME st;   //SYSTEMTIME  :Windows环境下32位汇编语言程序设计

GetLocalTime(&st);

其中：
```c
STRUCT SYSTEMTIME 
{
WORD wYear ; 年
WORD wMonth ;月
WORD wDayOfWeek ;星期，0=星期日，1=星期一...
WORD wDay ;日
WORD wHour ;时
WORD wMinute ;分
WORD wSecond ;秒
WORD wMilliseconds ;毫秒
}
```

**5、void ftime(struct timeb \*)**

#include <sys/timeb.h>

获取时间，有毫秒
struct timeb tp;
ftime(&tp);
     
其中：
```c
struct timeb{

    time_t time;   /* 为1970-01-01至今的秒数*/

    unsigned short millitm; /* 毫秒 */

    short timezone;  /* 时区差值，单位为分钟 */

    short dstflag;   /* 夏令时标识 */
 
};
```
```c
struct timeb{ 
    
    time_t time;   /* 为1970-01-01至今的秒数*/
     
    unsigned short millitm; /* 千分之一秒即毫秒 */
     
    short timezone;  /* 为目前时区和Greenwich相差的时间，单位为分钟 */
     
    short dstflag;   /* 为日光节约时间的修正状态，如果为非0代表启用日光节约时间修正 */
 
};
```

如何通过这两个结构获取系统的当前时间

struct timespec

可以通过 int clock_gettime(clockid_t clk_id, struct timespec *tp)来获取

```c
参数 clk_id : 检索和设置的clk_id指定的时钟时间。可以设置如下：

    CLOCK_REALTIME:系统实时时间,随系统实时时间改变而改变,即从UTC1970-1-1 0:0:0开始计时,如果 系统时间被用户改成其他,则对应的时间相应改变

    CLOCK_REALTIME_COARSE：和CLOCK_REALTIME类似，但是执行速度快，精度低

    CLOCK_MONOTONIC:从系统启动这一刻起开始计时,不受系统时间被用户改变的影响

    CLOCK_MONOTONIC_COARSE ：和CLOCK_MONOTONIC类似，但是执行速度快，精度低

    CLOCK_BOOTTIME：和CLOCK_MONOTONIC 类似，但是包括了系统休眠的时间。

    CLOCK_PROCESS_CPUTIME_ID:本进程到当前代码系统CPU花费的时间

    CLOCK_THREAD_CPUTIME_ID:本线程到当前代码系统CPU花费的时间
```

```c
struct timespec ts;

clock_gettime(CLOCK_REALTIME, &ts);
```

**8、gettimeofday()**
```c
int gettimeofday(struct timeval*tv, struct timezone *tz);

struct timeval{
long int tv_sec; // 1970年以来的秒数
long int tv_usec; // 微秒数
}
```
可以计算代码执行时间：
```
struct timeval tv_begin, tv_end;
gettimeofday(&tv_begin, NULL);
//...
gettimeofday(&tv_end, NULL);
```

9、GetTickCount（） 
它返回从操作系统启动到当前所经过的毫秒数，返回值以32位的双字类型DWORD存储，
因此可以存储的最大值是(2^32-1) ms约为49.71天，因此若系统运行时间超过49.71天时，这个数就会归0。 

11、TimeGetTime 
和GetTickCount差不多。GetTickCount精度15毫秒，TimeGetTime精度为1ms

**系统函数的转化关系如下：**

![系统函数的转化关系如下：](https://images2015.cnblogs.com/blog/937999/201604/937999-20160416155645738-366410882.jpg)



eg:
```c
#include <stdio.h>
#include <sys/time.h>
#include <time.h>

int main()
{

    long i = 10000000L;
    struct timespec ts;
    struct timeval tv;
    clock_t start, finish;
    double duration;
    long tv_micro_1, tv_micro_2, tv_micro;
    long ts_nano_1, ts_nano_2, ts_nano;

    gettimeofday(&tv, NULL);
    clock_gettime(CLOCK_REALTIME, &ts);
    start = clock();
    tv_micro_1 = tv.tv_usec;
    ts_nano_1 = ts.tv_nsec;
    printf("time val second is %ld\n", tv.tv_sec);
    printf("time val microsecond is %ld\n", tv.tv_usec);
    //clock_gettime(CLOCK_REALTIME,&ts);
    printf("\ntime spec second is %ld\n", ts.tv_sec);
    printf("time spec nanosecond is %ld\n", ts.tv_nsec);
    while (i--)
        ;

    gettimeofday(&tv, NULL);
    clock_gettime(CLOCK_REALTIME, &ts);
    tv_micro_2 = tv.tv_usec;
    ts_nano_2 = ts.tv_nsec;
    finish = clock();
    printf("\n\ntime val second is %ld\n", tv.tv_sec);
    printf("time val microsecond is %ld\n", tv.tv_usec);
    //clock_gettime(CLOCK_REALTIME,&ts);
    printf("\ntime spec second is %ld\n", ts.tv_sec);
    printf("time spec nanosecond is %ld\n", ts.tv_nsec);
    printf("-------------------\n");
    tv_micro = tv_micro_2 - tv_micro_1;
    ts_nano = ts_nano_2 - ts_nano_1;

    duration = (double)(finish - start) / CLOCKS_PER_SEC;
    printf("clock: %f seconds\n", duration);
    printf("timeval: %ld seconds\n", tv_micro);
    printf("timespec: %ld seconds\n", ts_nano);
    printf("-------------------\n");
```
>output:

```c
$ ./a
time val second is 1563182750
time val microsecond is 900252

time spec second is 1563182750
time spec nanosecond is 900260400


time val second is 1563182750
time val microsecond is 945784

time spec second is 1563182750
time spec nanosecond is 945790700
-------------------
clock: 0.046875 seconds
timeval: 45532 seconds
timespec: 45530300 seconds
```


## 设置系统时间


