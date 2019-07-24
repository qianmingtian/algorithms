#include <stdlib.h>
#include <stdio.h>

#define POLY 0x1021
/**
 * Calculating CRC-16 in 'C'
 * @para addr, start of data
 * @para num, length of data
 * @para crc, incoming CRC
 * 
 * 
 */
struct packet
{
    unsigned short head;
    unsigned short ttl;
    unsigned short crc;
} mac;

unsigned short crc16(unsigned char *addr, int num, unsigned int crc)
{
    int i;
    crc = 0xffff;
    for (; num > 0; num--) /* Step through bytes in memory */
    {
        crc = crc ^ (*addr++ << 8); /* Fetch byte from memory, XOR into CRC top byte*/
        for (i = 0; i < 8; i++)     /* Prepare to rotate 8 bits */
        {
            if (crc & 0x8000)            /* b15 is set... */
                crc = (crc << 1) ^ POLY; /* rotate and XOR with polynomic */
            else                         /* b15 is clear... */
                crc <<= 1;               /* just rotate */
        }                                /* Loop for 8 bits */
        crc &= 0xFFFF;                   /* Ensure CRC remains 16-bit value */
    }                                    /* Loop until num=0 */
    return (crc);                        /* Return updated CRC */
}

int main()
{
    mac.head = 2;
    mac.ttl = 1;
    mac.crc = 2;
    mac.crc = crc16(&mac, 3, mac.crc);

    printf("%x\n", mac.crc);
}
