/*
 * @Author: 千铭天
 * @Date: 2019-11-04 10:41:10
 * @LastEditors: 
 * @LastEditTime: 2019-11-04 11:12:50
 * @Description:  
 */
#include <stdio.h>
int index(int time_slot)
{
    int m, n;
    int node_index;
    m = ((time_slot + 625) % 500000) / 125000;
    n = ((time_slot + 625) % 500000) % 125000 / 1250 / 5;

    node_index = 4 * m + n + 1;

    return node_index;
}
int main()
{
    int time_slot,node;
    time_slot = 125000 * 2 + 1250 *16;
    node = index(time_slot);
    printf("node index is %d\n",node);
}