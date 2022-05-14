#include <stdio.h>

unsigned int set_nth_lsb_high(unsigned int x, int n){
	/**
	Set the nth LSB of x to 1.	
	*/

	unsigned int mask = 0b01;
	unsigned int temp = x | (mask << n); // xor doesn't work!
	return temp;

}

unsigned int toggle_nth_lsb(unsigned int x, int n){
	/**
	Set the nth LSB of x to be the opposite of what
	it used to be.
	*/

	unsigned int mask = 0b01;
	unsigned int temp = x ^ (mask << n);

}

unsigned int set_msb_high(unsigned int x){
	/**
	Set the most significant bit of x to 1.
	*/

	unsigned int mask = ~(0b0) ^ ((unsigned int)~(0b0) >> 1);
	return x | ((unsigned int) 0b01 << (sizeof(unsigned int) * 8 - 1));
	
}

int is_nth_high(unsigned int x, int n){

	return (x & (0b01 << n)) >> n; // or use != 0 to avoid shifting back

}

void print_bit_representation(unsigned int x){
	unsigned int tmp = x;
	// note -- the left shift **does** rely on casting to an unsigned type
	// Efe will be happy!
	unsigned int mask = (~0b0) ^ ((unsigned int)(~0b0) >> 1); // left shift here after casting
	unsigned int width = (~0b0);
	
	fprintf(stdout, "0b");
	
	while (width != 0){
		if ((mask & tmp) == 0){ // that bit is 0
			fprintf(stdout, "0");
		} else{fprintf(stdout, "1");}
		tmp <<= 1;
		width <<= 1;
	} fprintf(stdout, "\n");
}

int main(){
	unsigned int x = ~0b0;
	int result;
	
	x <<= 5;
	print_bit_representation(x);
	result = is_nth_high(x, 2);
	fprintf(stdout, "Original value, %dnd LSB is set to: %d\n", 2, result);
	
	x = set_nth_lsb_high(x, 2);
	print_bit_representation(x);
	result = is_nth_high(x, 2);
	fprintf(stdout, "After set, %dnd LSB is set to: %d\n", 2, result);
	
	x = toggle_nth_lsb(x, 2);
	print_bit_representation(x);
	result = is_nth_high(x, 2);
	fprintf(stdout, "After toggle, %dnd LSB is set to: %d\n", 2, result);
	
	x = toggle_nth_lsb(x, 2);
	print_bit_representation(x);
	result = is_nth_high(x, 2);
	fprintf(stdout, "After toggle, %dnd LSB is set to: %d\n", 2, result);
	
	x >>= 10;
	fprintf(stdout, "New x...\n");
	print_bit_representation(x);
	x = set_msb_high(x);
	fprintf(stdout, "After set MSB high:\n");
	print_bit_representation(x);
}