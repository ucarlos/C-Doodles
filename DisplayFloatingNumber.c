//
// Created by ulysses on 3/13/19.
//


#include "../common_header.h"
#include <math.h>
#include <stdbool.h>
// Defintions
#define FLOAT_SIZE (sizeof(float) * 8)
#define FLOAT_LEN (sizeof(float))
#define FLOAT_EXPONENT_BIAS (((1 << 7) - 1))


// Typedefs:
typedef unsigned char *byte_pointer;

// Structures:
typedef struct float_number{
    unsigned int sign_val;
    unsigned int exponent_val;
    unsigned int fractional;
    unsigned int byte_rep;
    int weighed_bias;
    float value;//
    long double signficand_val;

    /* Normalization Status
     * Status 0: Normalized Floating value (Exponent not 0 or 255)
     * Status 1: Denormalized Floating value (Exponent 0)
     * Status 2: Special_Case (Exponent 255)
     * Status 3: Byte Representation has been created, but Floating Point Number
     *           has not been seperated
     * Status 4: Initial Value
     * Status 5-7: NOT USED
     */
    struct{
        unsigned int value : 3;
    }Normalization_Status;

}Float_Number;

// Structure Functions Prototypes::
void intializeFloatNumber(struct float_number *fn, float value);
void Create_Bit_Representation(struct float_number *fn);
void Seperate_Floating_Number(struct float_number *fn);
void Print_Float_Number(struct float_number *fn);
void Generate_Sigificand_Number(struct float_number *fn);

// Helper Functions

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

void Convert_Unsigned_Integer_to_Binary(struct float_number *fn, char *string, int string_length){
    if (string_length < 1 || string_length > (FLOAT_SIZE - 1)){
        printf("Error: String Length must be positive and less than Max value of %u. Current length: %d"
                , (unsigned)(FLOAT_SIZE), string_length);
        exit(EXIT_FAILURE);
    }
    // Intentionally reversed:
    unsigned int value = fn->fractional;
    for (int i = 0; i < FLOAT_SIZE; i++, value >>= 1){
        string[i] = (char) ((value & 0x1) + '0');
    }
    string[string_length + 1] = '\0';
}

// Not really needed, but OK
void Reverse_String(char *string, int string_length){
    char *temp = calloc(1, sizeof(char));
    for (int i = 0; i < (string_length/ 2); i++){
        *temp = string[i];
        string[i] = string[string_length - i];
        string[string_length - i] = *temp;
    }
}


// Structure Functions:

void intializeFloatNumber(struct float_number *fn, float value){
    fn->Normalization_Status.value = 4;
    fn->value = value;

}

void Create_Bit_Representation(struct float_number *fn){
    char *string = calloc(FLOAT_SIZE, sizeof(char));
    byte_pointer float_address = (byte_pointer) &fn->value;
    char *endpoint;
    int i;
    char *sp = string;
    for (i = 0; i < FLOAT_LEN; i++){
        sprintf((sp), "%.2x", float_address[i]);
        sp += 2;
    }

    Reverse_Bit_Representation(string, (int)strlen(string));

    // Now read into fn:
    fn->byte_rep = (unsigned) strtol(string, &endpoint, 16);
    // Change Status:
    fn->Normalization_Status.value = 3;
    free(string);
}


void Seperate_Floating_Number(struct float_number *fn){
    // Get Sign value:
    fn->sign_val =(fn->byte_rep & 0x80000000) >> 31;
    // Get Exponent Value:
    fn->exponent_val = (fn->byte_rep & 0x7f800000) >> 23;
    // Get Fraction Value
    fn->fractional = (fn->byte_rep & 0x007fffff);

    //Generate Normalization Value:
    fn->Normalization_Status.value = (fn->exponent_val == 255) ? 2:
                                     (fn->exponent_val == 0) ? 1 : 0;

    //Generate Bias for Normalized and Denormalized values:
    if (fn->Normalization_Status.value != 2){
        fn->weighed_bias = (!fn->Normalization_Status.value) ? ((int)fn->exponent_val - FLOAT_EXPONENT_BIAS)
                : (1 - FLOAT_EXPONENT_BIAS);
    }

}

void Generate_Sigificand_Number(struct float_number *fn){
    if (fn->Normalization_Status.value >= 3){
        printf("Error: Floating Number has not been Separated Yet. Aborting.");
        return;
    }
    fn->signficand_val = significandl(fn->value);
}
void Print_Float_Number(struct float_number *fn){
    if (fn->Normalization_Status.value >= 3){ // Considers case 3, 4, and 5, 6, 7(Not used)
        printf("Error: This Number has not been processed yet. Aborting.");
        return;
    }

    printf("Inital Number: %.3f\n", fn->value);
    printf("Bit Representation (In Hexadecimal) : 0x%x\n", fn->byte_rep);
    printf("Sign Value: %u\n", fn->sign_val);
    printf("Exponent Value: %u\n", fn->exponent_val);
    printf("Fractional Value: 0x%x\n", fn->fractional);

    printf("This Floating Point Number is ");
    if (fn->Normalization_Status.value == 2)
        printf("classified as a Special Case Floating Number.\n");
    else if (fn->Normalization_Status.value == 1)
        printf("classified as a De-Normalized Floating Number.\n");
    else printf("classified as a Normalized Floating Number.\n");

    if (fn->Normalization_Status.value != 2){
        printf("The weighed Bias value : %d\n", fn->weighed_bias);
        printf("So in M * 2^E form, the number %f is represented as " , fn->value);
            printf("%.24Lf * 2^%d\n", fn->signficand_val, fn->weighed_bias);
    }

}



int main(void){
    float num;
    puts("Please enter a number:");
    scanf("%f", &num);

    struct float_number *fn = calloc(1, sizeof(struct float_number));
    intializeFloatNumber(fn, num);
    Create_Bit_Representation(fn);
    Seperate_Floating_Number(fn);
    Generate_Sigificand_Number(fn);
    Print_Float_Number(fn);


    free(fn);
    return 0;


}
