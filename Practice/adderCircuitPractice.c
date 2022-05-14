#include <stdio.h>
#include <stdlib.h>


void print_bit_representation(unsigned char x) {
    unsigned char tmp = x;
    unsigned char mask = (~0b0) ^ ((unsigned char)(~0b0) >> 1); // need to cast to unsigned char for right shift (cast first)
    unsigned char width = (~0b0);

    while (width != 0) {
        if ((mask & tmp) == 0) { // that bit is 0
            printf("0");
        }
        else {
            printf("1");
        }

        width <<= 1;
        tmp <<= 1;
    }
    printf("\n");
}


unsigned char bitwise_adder(unsigned char x, unsigned char y) {
    // start with LSB
    unsigned char mask = 0b01; // one mask
    unsigned char r = 0, c = 0, sum = 0; // initialize everything to 0
    int bit_counter = 0; // tracking digit

    while (x != 0 || y != 0) { // if either one is not equal to 0
        r = (mask&x)^(mask&y)^(mask&c); // calculating r with values at current digit and previous carry over (0 for first)
        c = ((mask&x) & (mask&y)) | ((mask&x) & (mask&c)) | ((mask&y) & (mask&c)); // calculating new carry over
        x >>= 1; // shifting to next digit
        y >>= 1;
        sum |= ((mask&r)<<bit_counter); // adding to right rigit in sum
        bit_counter++; // incrementing digit
    }

    sum |= ((mask&c)<<bit_counter); // adding last carry over
}


int main(void) {
	unsigned char x = 42;
	unsigned char y = 150;
	unsigned char z = bitwise_adder(x, y);
	fprintf(stdout, "The sum of %u and %u is %u\n", x, y, z);
	print_bit_representation(x);
	print_bit_representation(y);
	print_bit_representation(z);
	
	x = 200;
	y = 120;
	z = bitwise_adder(x, y);
	//overflow here
	fprintf(stdout, "The sum of %u and %u is %u\n", x, y, z);
	print_bit_representation(x);
	print_bit_representation(y);
	print_bit_representation(z);
	
	x = 99;
	y = 12;
	z = bitwise_adder(x, y);
	fprintf(stdout, "The sum of %u and %u is %u\n", x, y, z);
	print_bit_representation(x);
	print_bit_representation(y);
	print_bit_representation(z);

    return 0;
}