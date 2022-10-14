#include "./common_header.h"
/*
 * Suppose we number the bytes in a w-bit word from 0(Least significant) to
 * w/8 - 1 (Most significant). Write code for the following C function, which 
 * will return an unsigned value in which byte i of argument x has been replaced 
 * by byte b:
 * 
 * unsigned replace_byte(unsigned x, int i, unsigned char b);
 * 
 * Here are some examples showing how the function should work:
 * 
 * replace_byte(0x12345678, 2, 0xAB) --> 0x12AB5678
 * replace_byte(0x12345678, 0, 0xAB) --> 0x123456ab
 */
#define MOVE_BITS(x, i) ((0U | (unsigned)(x)) << (8 * i))

unsigned int replace_byte(unsigned int x, int i, unsigned char b);

int main(void){
    unsigned int value = 0x12345678;
    unsigned char mask = 0xab;
    int shift;
    printf("Please enter a Byte location from (0 to %d):",
           (int)sizeof(unsigned) - 1 );
    scanf("%d", &shift);
    
    printf("Original Value: 0x%x\n", value);
    printf("Mask Value: 0x%x\n", mask);
    printf("After Replacing Byte %d with Mask: 0x%x\n", shift,
           replace_byte(value, shift, mask));

    return 0;

}

unsigned int replace_byte(unsigned int x, int i, unsigned char b){
    if ((i < 0) || (i >= sizeof(unsigned int))){
        printf("Byte location cannot be negative or exceed"
               "%d bytes\n", (int)(sizeof(unsigned int) - 1));
                   
        exit(EXIT_FAILURE);
    }

/*
 * First, make a copy of the variable x (Or use it)
 * Second, make a variable y that shifts b by 8 * i
 * Third, Create a mask of ff and shift it by 8 * i.
 * Fourth, Negate the mask and do a BITWISE AND on x (or copy) to clear the location you want
 *        and to ignore the other bits
 * Lastly, Do a BITWISE OR on the result.
 *
 */ 
    unsigned int copy = x;
    unsigned int shift = (0U | (unsigned) b) << (8 * i);
    //copy &= (~((0U | 0xff) << 8 * i));
    //copy |= shift;

    copy = ((copy & ~MOVE_BITS(0xff, i)) | MOVE_BITS(b, i)); // In one line
    return copy;
    

}
