#include <stdio.h>
#include <sys/time.h> //timeval?
#include <time.h>

int main()
{
    int j = 5;

    // while (j--)
    // {
    //     /* code */

    //     long i = 10000000L;
    //     struct timespec ts;
    //     struct timeval tv;
    //     clock_t start, finish;
    //     double duration;
    //     long tv_micro_1, tv_micro_2, tv_micro;
    //     long ts_nano_1, ts_nano_2, ts_nano;

    //     gettimeofday(&tv, NULL);
    //     clock_gettime(CLOCK_REALTIME, &ts);
    //     start = clock();
    //     tv_micro_1 = tv.tv_usec;
    //     ts_nano_1 = ts.tv_nsec;
    //     printf("\ntime val second is %ld\n", tv.tv_sec);
    //     printf("time val microsecond is %ld\n", tv.tv_usec);
    //     //clock_gettime(CLOCK_REALTIME,&ts);
    //     printf("\ntime spec second is %ld\n", ts.tv_sec);
    //     printf("time spec nanosecond is %ld\n", ts.tv_nsec);

    //     while (i--)
    //         ;

    //     gettimeofday(&tv, NULL);
    //     clock_gettime(CLOCK_REALTIME, &ts);
    //     tv_micro_2 = tv.tv_usec;
    //     ts_nano_2 = ts.tv_nsec;
    //     finish = clock();
    //     printf("\n\ntime val second is %ld\n", tv.tv_sec);
    //     printf("time val microsecond is %ld\n", tv.tv_usec);
    //     //clock_gettime(CLOCK_REALTIME,&ts);
    //     printf("\ntime spec second is %ld\n", ts.tv_sec);
    //     printf("time spec nanosecond is %ld\n", ts.tv_nsec);
    //     printf("-------------------\n");
    //     tv_micro = tv_micro_2 - tv_micro_1;
    //     ts_nano = ts_nano_2 - ts_nano_1;

    //     duration = (double)(finish - start) / CLOCKS_PER_SEC;
    //     printf("clock: %f seconds\n", duration);
    //     printf("timeval: %ld seconds\n", tv_micro);
    //     printf("timespec: %ld seconds\n", ts_nano);
    //     printf("-------------------\n");
    //     printf("修改本地时间\n");
    //     printf("-------------------\n");

    //     printf("time val second is %ld\n", tv.tv_sec);
    //     printf("time val microsecond is %ld\n", tv.tv_usec);
    //     tv.tv_sec += 100;
    //     tv.tv_usec += 10;
    //     int settimeofday(const struct timeval *tv, const struct timezone *tz);
    //     printf("time val second is %ld\n", tv.tv_sec);
    //     printf("time val microsecond is %ld\n", tv.tv_usec);
    //     printf("time val microsecond is %x\n", tv.tv_usec);
    // }
}
