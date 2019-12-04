/*
 * @Author: 千铭天
 * @Date: 2019-10-28 09:19:09
 * @LastEditors: 
 * @LastEditTime: 2019-11-04 10:02:52
 * @Description:  
 */
#include <stdio.h>
struct packet
{
    int num;
    int name;
};

void forward(struct packet *m)
{
    m->num = 2;
}

int re(int input)
{
    if (input < 9)
        return 1;
    else
        return 0;
}

int main()
{
    struct packet mac;
    mac.name = 1;
    mac.num = 1;

    forward(&mac);

    printf("%d", mac.num);
    if (re(10))
    {
        printf("this number is smaller than 9");
    }
    else
    {
        printf("this number is bigger than 9");
    }
}