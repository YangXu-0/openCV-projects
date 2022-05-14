#include <stdlib.h>
#include <stdio.h>

long Q4_macros(long red, long green, long blue) {
    long temp = 0;

    temp ^= blue << 16;
    temp ^= green << 8;
    temp ^= red;

    return temp;
    // blue << 16 | green << 8 | red
}

unsigned int rotate_left(unsigned int i, int n) {
    unsigned int temp = i;
    int size = sizeof(unsigned int) * 8;
    for (int j = 0; j < n; j++) {
        unsigned int mask = 0b01 << size - 1;
        mask = mask & temp;
        mask = mask << size - 1;
        temp = temp << 1;
        temp = temp | mask; 
    }

    return temp;
}

unsigned int rotate_right(unsigned int i, int n) {
    unsigned int temp = i;
    int size = sizeof(unsigned int) * 8;
    for (int j = 0; j < n; j++) {
        unsigned int mask = 0b01;
        mask &= temp;
        mask <<= size - 1;
        temp >>= 1;
        temp |= mask;
    }

    return temp;
}

unsigned int sol_rotate_left(unsigned int i, int n)
{
    return (i << n) | (i >> (sizeof(int) * 8) - n);
}

unsigned int sol_rotate_right(unsigned int i, int n)
{
    return (i << (sizeof(int) * 8) - n) | (i >> n);
}

int main(void) {
    // Pg. 525 Q # 1, 2, 4, 7
    
    /*
    // Q1 A
    int i = 8; // 00001000 --> 00000100
    int j = 9; // 00001001 --> 00000100
    printf("%d", i >> 1 + j >> 1); // 0 

    // Q1 B
    int i = 1; // 00000001 -> 11111110
    printf("%d", i & ~i); // 0

    // Q1 C
    // 00000010 00000001 00000000
    // 00000000 00000000
    // 00000000 -> 0

    // Q1 D
    // 00000111 00001000 00001001
    // 00000111 ^ 00001000
    // 00001111 -> 15

    // Q2
    int mask = 0b01;
    mask <<= 3;
    int temp = 0;
    temp ^= mask;
    printf("%d", temp);
    */

    // Q4

    // Q7
    printf("%d %d\n", rotate_left(13, 5), sol_rotate_left(13, 5));
    printf("%d %d\n", rotate_right(13, 5), sol_rotate_right(13, 5));

    return 0;
}