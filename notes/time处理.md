## **参考网址：**

1.[C语言的时间函数](http://bjtime.cn/info/view.asp?id=307)

2.[struct timespec 和 struct timeval](https://www.cnblogs.com/book-gary/p/3716790.html)

3.[Linux系统时间函数](https://blog.csdn.net/qinrenzhi/article/details/81252377)

4.[C语言之间函数(4)之Linux下设置时间的函数stime()和settimeofday()](https://blog.csdn.net/qq_33706673/article/details/79008071)

**5.x86毫秒级的中断如何实现微秒的时间：**[浅谈时间函数gettimeofday的成本
](https://blog.csdn.net/russell_tao/article/details/7185588)

**6.settimeofday() 将时间设置到墙上时间wall_jiffies:**[系统调用之sys_settimeofday](https://blog.csdn.net/tiantao2012/article/details/80199474)


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


## **设置系统时间**

**系统函数的转化关系如下：**


![系统函数的转化关系如下：](https://images2015.cnblogs.com/blog/937999/201604/937999-20160416155645738-366410882.jpg)



mktime()函数可以将struct tm转换成time_t，其声明如下：

>time_t mktime (struct tm *timeptr);



Linux下设置系统时间：

**标准C库中只有获取系统时间的API，好像还没有设置系统时间的API**

获取系统时间有两个途径，一种是从CMOS中读，一种是从系统中读，但修改时间却只有一种，即修改linux系统中的时间，而修改CMOS中的时间是无效的，因为CMOS中的时间会被定时重写掉。

1．Linux下设置系统时间的函数有好几个，先来看看最常用的stime()函数，这个函数只能精确到**秒**。
```c
#define _SVID_SOURCE /*如果你使用的是glib2的话，必须先定义这个宏才能使用*/

#include <time.h>

int stime(time_t *t);
```
2．通过settimeofday()函数来设置系统时间，这个函数设置的精度可以精确到**微秒**。
```c
#include <sys/time.h> //或者

#include <time.h>

struct timeval tv;

printf("time val second is %ld\n", tv.tv_sec);

printf("time val microsecond is %ld\n", tv.tv_usec);

tv.tv_sec+=10;

tv.tv_usec+=10;
/*settimeofday调用sys_settimeofday,sys_settimeofday调用do_settimeofday完成时间的修改，将tv变量存储的时间修改到xtime.

gettimeofday<-sys_gettimeofday<-do_gettimeofday从xtime将时间读取出来
*/
 if(settimeofday(&tv, NULL)){
        printf("fault");
    }

printf("time val second is %ld\n", tv.tv_sec);

printf("time val microsecond is %ld\n", tv.tv_usec);
```


有些系统调用在GLIBC里是找不到相应的函数的. 这一类函数会按照 sysdeps/unix/syscall-template.S 里的参数要求在 sysdeps/unix/syscall.S里定义每一个系统调用. 编译的时候,sysdev/unix/make-syscalls.sh 会根据上面的文件生成每个函数的汇编代码到 glibc库里面.

**Unix系统**

在Unix类的操作系统中，调用sleep()函数需要一个以秒为单位的参数，需要更精确的时间控制可以使用nanosleep()函数。

![NTP客户端与服务器的交互过程](https://img-blog.csdn.net/20180811164448323?watermark/2/text/aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2Rvc3RoaW5n/font/5a6L5L2T/fontsize/400/fill/I0JBQkFCMA==/dissolve/70)

客户端和服务端都有一个时间轴，分别代表着各自系统的时间，当客户端想要同步服务端的时间时，客户端会构造一个NTP协议包发送到NTP服务端，客户端会记下此时发送的时间t0，经过一段网络延时传输后，服务器在t1时刻收到数据包，经过一段时间处理后在t2时刻向客户端返回数据包，再经过一段网络延时传输后客户端在t3时刻收到NTP服务器数据包。特别声明，t0和t3是客户端时间系统的时间、t1和t2是NTP服务端时间系统的时间，它们是有区别的。对于时间要求不那么精准设备，直接使用NTP服务器返回t2时间也没有太大影响。但是作为一个标准的通信协议，它是精益求精且容不得过多误差的，于是必须计算上网络的传输延时。客户端与服务端的时间系统的偏移定义为θ、网络的往返延迟定义为δ，基于此，可以对t2进行精确的修正，已达到相关精度要求，它们的计算公式如下：


$t_1-(t_0+δ) = θ$

$t_0+δ$:在$t_1$时刻，服务器走到$t_0+δ$

$t_3-(t_2+δ) = θ$

$t_2+δ$:在$t_3$时刻，服务器走到$t_2+δ$

$θ=\frac{(t_1-t_0)+(t_2-t_3)}{2}$

$δ =(t_3-t_0)-(t_2-t_1)$



## settimeofday使用出现的问题 ：
    1.settimeofday成功返回0，错误返回-1

    2.settimeofday errno错误码:
            EFAULT表示传递的参数错误，如时间值是无效的值，Invalid argument 

            EPERM表示权限不够，注意只有root用户才有修改系统时间的权限。
                
                如果要让普通程序修改系统时间，可以先切换到root用户操作，修改完成后，再切换到普通用户

                或者用命令chmod +s给执行文件加上root用户的权限。
            
            关于参数不合法：
                1.时间设置有下限,为使得进行矫正的后20位置0，直接赋值tv_sec = 0x1000000
                
```c
    #include <errno.h>

    gettimeofday(&current_time, NULL);
    printf("current_time sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);
    current_time.tv_sec = 0;
    current_time.tv_usec = 0;
    flag = settimeofday(&current_time, NULL);
    printf("%s\n", strerror(errno)); // 间接使用strerror输出错误字符串
    if (flag)
    {
        printf("\nflag  %d\n\n", flag);
    };

    gettimeofday(&current_time, NULL);
    printf("init_time    sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);

```
```c
current_time sec 1563934934  729678
Invalid argument
flag  -1
init_time    sec 1563934934  730153  
```
```c
    #include <errno.h>

    gettimeofday(&current_time, NULL);
    printf("current_time sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);
    current_time.tv_sec -= 3000;
    current_time.tv_usec = 0;
    flag = settimeofday(&current_time, NULL);
    printf("%s\n", strerror(errno)); // 间接使用strerror输出错误字符串
    if (flag)
    {
        printf("\nflag  %d\n\n", flag);
    };

    gettimeofday(&current_time, NULL);
    printf("init_time    sec %ld  %ld\n", current_time.tv_sec, current_time.tv_usec);
```

```c
current_time sec 1563934695  770393
Success
init_time    sec 1563931695  83  
```

```c
    current_time.tv_sec = current_time.tv_sec - 1563000000; //
    current_time.tv_usec = 3;
 

    current_time sec 1563940140  260865
    Success
    init_time    sec 940140  76   
```
