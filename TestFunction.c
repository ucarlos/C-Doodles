//
// Created by ulysses on 3/12/19.
//
#include "../common_header.h"
#include <math.h>
#define FLOAT_SIZE (sizeof(float) * 8)
#define DOUBLE_SIZE (sizeof(double) * 8)
typedef unsigned char *byte_pointer;
void Get_Bit_Representation(char *string, byte_pointer float_address, int type_length);
void Reverse_Bit_Representation(char *string, int string_length);

int main(void){
    char *string = calloc(FLOAT_SIZE, sizeof(char));
    float number = 15;
    Get_Bit_Representation(string, (byte_pointer) &number, sizeof(float));
    Reverse_Bit_Representation(string, strlen(string));
    printf("Float Value: %.3f\n", number);

    printf("Bit Representation (Hexadecimal): ");
    puts(string);
    long long test;
    printf("%lu\n", sizeof(test));



}
// If on Little-Endian Machine, then Bit Reprensentation is reversed. Big-Endian Machines don't need this.
void Get_Bit_Representation(char *string, byte_pointer float_address, int type_length){
    // Going to assume little-endian machine:
    int i;
    char *sp = string;
    for (i = 0; i < type_length; i++){
        sprintf((sp), "%.2x", float_address[i]);
        sp += 2;
    }

}

void Reverse_Bit_Representation(char *string, int string_length){
    int limit = string_length / 2;
    int end_point = string_length;
    char temp1, temp2;
    for (int i = 0; i < limit; i += 2){
        end_point -= 2;

        temp1 = string[i];
        temp2 = string[i + 1];
        string[i] = string[end_point];
        string[i + 1] = string[end_point + 1];
        string[end_point] = temp1;
        string[end_point + 1] = temp2;


    }
}