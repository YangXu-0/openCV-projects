/*
Changes from live-coding session in class:
Line 37, bitwise_adder(): incorrect final update to sum
*/
#include <stdio.h>

void print_bit_representation(unsigned char x){
	unsigned char tmp = x;
	// note -- the right shift **does** rely on casting to an unsigned type
	unsigned char mask = (~0b0) ^ ((unsigned char)(~0b0) >> 1); // right shift here after casting
	unsigned char width = (~0b0);
	
	while (width != 0){
		if ((mask & tmp) == 0){ // that bit is 0
			fprintf(stdout, "0");
		} else{fprintf(stdout, "1");}
		tmp <<= 1;
		width <<= 1;
	} fprintf(stdout, "\n");
}


unsigned char bitwise_adder(unsigned char x, unsigned char y){
	//start with LSB
	unsigned char mask  = 0b01;
	unsigned char r=0, c=0, sum = 0;
	int bit_counter = 0;
	while(x!=0 || y!=0){
		r = ((mask&x)^(mask&y)^(mask&c));
		c =  ((mask &x) &(mask&y))|((mask&x)&(mask&c))|((mask&c)&(mask&y)); 
		x>>=1;
		y>>=1;
		sum |= ((mask&r)<<bit_counter);
		bit_counter++;
	}
	sum |= ((mask&c)<<bit_counter); 
	//Not sum |= ((mask&r)<<bit_counter); because should be adding the last carry-over
	return sum;
}

int main(){
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