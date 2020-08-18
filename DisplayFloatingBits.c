//
// Created by ulysses on 3/9/19.
//

#include "../common_header.h"
#define FLOAT_BIAS (127)
#define FLOAT_SIZE (32)

void display_float_bits(float value);
void Convert_Fractional_Part_to_String(char *string, int string_length, unsigned value);
void Reverse_String(char *string, int string_length);
void Convert_Unsigned_To_Binary(char *string, int string_length, unsigned value);
void fputss(char *string);
double Fractional_to_Decimal(char *string, int string_length);
void Convert_Float_to_Binary_Representation(char *string, int string_length, float value){

}


int main(void){
    //float value;
    //puts("Enter a floating-point value:");
    //scanf("%f", &value);
    float value = 16;
    char *string = calloc(FLOAT_SIZE, sizeof(char));

    printf("Numerical Value: %f\n", value);
    //display_float_bits(value);

    Convert_Unsigned_To_Binary(string, FLOAT_SIZE - 1, value);
    fputss(string);
    free(string);

}

double Fractional_to_Decimal(char *string, int string_length){
    double sum = 1;
    for (int i = 0; i < FLOAT_SIZE; i++){
        if ((int)string[i])
            sum += (1.0 / (1 << i));
    }
    return sum;

}

void display_float_bits(float value){
    char *string = calloc(FLOAT_SIZE, sizeof(char));
    unsigned int_value = (unsigned)value;

    unsigned sign = (int_value &  0x80000000) >> 31; //Store only the sign
    unsigned exponent = (int_value & 0x7f800000) >> 16; // Store only the exponent
    unsigned fractional = int_value & 0x007fffff; // Store only the fractional part (Significand)
    unsigned bias = exponent - FLOAT_BIAS;
    Convert_Fractional_Part_to_String(string, FLOAT_SIZE - 1, fractional);

    // Convert Fractional Part to Mantisa:
    double Significand = Fractional_to_Decimal(string, FLOAT_SIZE);
    printf("%f\n", Significand);


}

// Not needed:,
void Convert_Fractional_Part_to_String(char *string, int string_length, unsigned value){
    if (string_length < 1 || string_length > (FLOAT_SIZE - 1)){
        printf("Error: String Length must be positive and less than Max value of %u. Current length: %d"
        , (FLOAT_SIZE), string_length);
        exit(EXIT_FAILURE);
    }
    // Intentionally reversed:
    for (int i = 0; i < FLOAT_SIZE; i++, value >>= 1){
        string[i] = (value & 0x1) + '0';
    }
    string[string_length + 1] = '\0';
}

void Reverse_String(char *string, int string_length){
    char *temp = calloc(1, sizeof(char));
    for (int i = 0; i < (string_length/ 2); i++){
        *temp = string[i];
        string[i] = string[string_length - i];
        string[string_length - i] = *temp;
    }
}

void Convert_Unsigned_To_Binary(char *string, int string_length, unsigned value){
    char *copy = calloc(FLOAT_SIZE, sizeof(char));
    strncpy(copy, string, FLOAT_SIZE);
    Convert_Fractional_Part_to_String(copy, string_length, value);
    //Reverse_String(copy, string_length);
    strncpy(string, copy, FLOAT_SIZE);
    free(copy);

}

void fputss(char *string){
    fputs(string, stdout);
    puts("");
}

void Convert_Float_to_Binary(char *string, int string_length, float value){

}
/* TO DO : CREATE A FUNCTION THAT CONVERTS SOMETHING TO A BYTE, USE STOI TO CONVERT BINARY STRING TO DECIMAL */