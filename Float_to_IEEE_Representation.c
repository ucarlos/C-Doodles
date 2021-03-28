//
// Created by ulysses on 3/13/19.
//

#include "./common_header.h"
#include <math.h>
#include <stdbool.h>
// Defintions

#define FLOAT_SIZE (sizeof(float) * 8)
#define FLOAT_LEN (sizeof(float))
#define FLOAT_EXPONENT_BIAS (((1 << 7) - 1))
#define FLOAT_EXP_LEN (8)
#define FLOAT_FRAC_LEN (23)
#define FLOAT_MAX_EXPONENT_VAL ((1 << 8) - 1)

#define DOUBLE_SIZE (2 * FLOAT_SIZE)
#define DOUBLE_LEN (sizeof(double))
#define DOUBLE_EXPONENT_BIAS (((1 << 10) - 1))
#define DOUBLE_EXP_LEN (11)
#define DOUBLE_FRAC_LEN (52)
#define DOUBLE_MAX_EXPONENT_VAL ((1 << 11) - 1)

// Bit Masks:
#define FLOAT_SIGN_MASK (0x80000000)
#define FLOAT_EXP_MASK (0x7f800000)
#define FLOAT_FRAC_MASK (0x007fffff)
#define DOUBLE_SIGN_MASK (0x8000000000000000)
#define DOUBLE_EXP_MASK (0x7ff0000000000000)
#define DOUBLE_FRAC_MASK (0x000fffffffffffff)

// Typedefs:
typedef unsigned char *byte_pointer;

// Assuming that
typedef struct float_number{
	unsigned long long int sign_val;
	unsigned long long int exponent_val;
	unsigned long long int fractional;
	unsigned long long int byte_rep;
	int weighed_bias;
	bool isDouble;

    //Union to seperate float and double:
	union datatype_value{
		double double_value;
		float float_value;
	}value;
    long double signficand_val;

    /* Normalization Status
     * Status 0: Normalized Floating value (Exponent not 0 or 255(2047) )
     * Status 1: Denormalized Floating value (Exponent 0)
     * Status 2: Special_Case (Exponent 255(2047) )
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
void Initialize_Floating_Number(struct float_number *fn);
void Create_Bit_Representation(struct float_number *fn);
void Seperate_Floating_Number(struct float_number *fn);
void Print_Float_Number(struct float_number *fn);
void Generate_Sigificand_Number(struct float_number *fn);
void Print_Error_Message(unsigned int error_code);
void Print_Instructions(void);

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


// Structure Functions:

void Print_Instructions(void){
	printf("This Program evaluates a Float (32-bit Floating-point) "
        "or a Double (64-bit Floating-point) value.\n");
	printf("If you plan on using a Float number, Please input 1. "
        "If you plan on using a Double number, "
        "Please input 2.\n");
	printf("If you are not sure, please input 2.\n");
	
}

void print_dash_line(void){
    for (int i = 0; i < 90; i++)
        putchar('-');
    printf("\n");
};

void Print_Error_Message(unsigned int error_code){
    printf("Error: ");
    switch(error_code){
        case 2:
            printf("Cannot use a Special-Case "
                   "Floating-Point Number for this situation.\n");
            break;
        case 3:
            printf("The Floating-Point Case "
                   "for this number has not been generated.\n");
            break;
        case 4:
            printf("The Bit-level Representation "
                   "has yet to be created for this Floating-Point Number.\n");
            break;
        default:
            printf("If you are seeing this message, "
                   "it means that you inputted an error code that does not exist.\n");
            break;
    }
}

void Initialize_Floating_Number(struct float_number *fn){
	float float_num;
	double double_num;
	int test;
    Print_Instructions();

	scanf("%d", &test);
	
	if (!(test == 1 || test == 2)){
		printf("Invalid Input. This program will now close.");
		exit(EXIT_FAILURE);
	}

	puts("Now please enter a number:");
	if (test == 1){
		scanf("%f", &float_num);
		fn->value.float_value = float_num;
		fn->isDouble = false;
	}
	else {
        scanf("%lf", &double_num);
        fn->value.double_value = double_num;
        fn->isDouble = true;
    };

	fn->Normalization_Status.value = 4;
    system("clear");
}

void Create_Bit_Representation(struct float_number *fn){
    int string_size = (fn->isDouble) ? DOUBLE_SIZE : FLOAT_SIZE;
    char *string = calloc(string_size, sizeof(char));
    byte_pointer float_address = (byte_pointer) &fn->value;
    char *endpoint;
    int i;
    char *sp = string;
    int loop_end = (fn->isDouble) ? DOUBLE_LEN : FLOAT_LEN;
    for (i = 0; i < loop_end; i++){
        sprintf((sp), "%.2x", float_address[i]);
        sp += 2;
    }

    Reverse_Bit_Representation(string, (int)strlen(string));

    // Now read into fn:
    fn->byte_rep = (unsigned long long int) strtoll(string, &endpoint, 16);
    // Change Status:
    fn->Normalization_Status.value = 3;
    free(string);
}


void Seperate_Floating_Number(struct float_number *fn){
    if (fn->Normalization_Status.value > 3){
        Print_Error_Message(4);
        return;
    }
    // Difference Masks are used depending on float/double
    // and are right-shifted depending on the length of the data type
    if (fn->isDouble){
        fn->sign_val = (fn->byte_rep & DOUBLE_SIGN_MASK) >> (DOUBLE_EXP_LEN + DOUBLE_FRAC_LEN);
        fn->exponent_val = (fn->byte_rep & DOUBLE_EXP_MASK) >> (DOUBLE_FRAC_LEN);
        fn->fractional = (fn->byte_rep & DOUBLE_FRAC_MASK);
    }
    else {
        // Convert to unsigned int to make sure the bit operations work for Float:
        unsigned int bit_rep = (unsigned int)fn->byte_rep;
        // Get Sign value:

        fn->sign_val = (bit_rep & FLOAT_SIGN_MASK) >> (FLOAT_EXP_LEN + FLOAT_FRAC_LEN);
        // Get Exponent Value:
        fn->exponent_val = (bit_rep & FLOAT_EXP_MASK) >> (FLOAT_FRAC_LEN);
        // Get Fraction Value
        fn->fractional = (bit_rep & FLOAT_FRAC_MASK);
    }

    //Generate Normalization Value:
    if (fn->isDouble)
        fn->Normalization_Status.value = (fn->exponent_val == DOUBLE_MAX_EXPONENT_VAL) ? 2 :
                                         (fn->exponent_val == 0) ? 1 : 0;
    else
        fn->Normalization_Status.value = (fn->exponent_val == FLOAT_MAX_EXPONENT_VAL) ? 2:
                                         (fn->exponent_val == 0) ? 1 : 0;

    //Generate Bias for Normalized and Denormalized values:
    if (fn->Normalization_Status.value != 2){
        if (fn->isDouble)
           fn->weighed_bias = (!fn->Normalization_Status.value) ?
                   ((int) fn->exponent_val - DOUBLE_EXPONENT_BIAS)
                   : (1 - DOUBLE_EXPONENT_BIAS);
        else
            fn->weighed_bias = (!fn->Normalization_Status.value) ?
                    ((int)fn->exponent_val - FLOAT_EXPONENT_BIAS)
                    : (1 - FLOAT_EXPONENT_BIAS);
    }

}

void Generate_Sigificand_Number(struct float_number *fn){
    if (fn->Normalization_Status.value >= 3){
        Print_Error_Message(3);
        return;
    }

    fn->signficand_val = (fn->isDouble) ? significandl(fn->value.double_value) :
            significandl(fn->value.float_value);
}

void Print_Float_Number(struct float_number *fn){
    if (fn->Normalization_Status.value >= 3){ // Considers case 3, 4, and 5, 6, 7(Not used)
        Print_Error_Message(3);
        return;
    }
    print_dash_line();
    if (fn->isDouble)
        printf("Initial Number: %.4f (Double Precision)\n", fn->value.double_value);
    else
        printf("Initial Number: %.4f (Single Precision)\n", fn->value.float_value);


    printf("Bit Representation (In Hexadecimal): 0x%llx\n", fn->byte_rep);
    printf("Sign Value: %llu\n", fn->sign_val);
    printf("Exponent Value: %llu\n", fn->exponent_val);
    printf("Fractional Value (In Hexadecimal): 0x%llx\n", fn->fractional);

    printf("Floating-Point Classification: ");
    if (fn->Normalization_Status.value == 2)
        printf("Special Case (Exponent field is all ones)\n");
    else if (fn->Normalization_Status.value == 1)
        printf("Denormalized(Exponent field is all zeros)\n");
    else
        printf("Normalized\n");

    if (fn->Normalization_Status.value != 2){
        printf("The weighed Bias value : %d\n", fn->weighed_bias);
        printf("So in M * 2^E form, the number ");

        if (fn->isDouble)
            printf(" %.4f is represented as ", fn->value.double_value);
        else
            printf(" %.4f is represented as ", fn->value.float_value);

        printf("%.24Lf * 2^%d\n", fn->signficand_val, fn->weighed_bias);
    }
    printf("When multiplied, the result is %.24Lf\n", fn->signficand_val * pow(2, fn->weighed_bias));
    print_dash_line();

}



int main(void){
    struct float_number *fn = calloc(1, sizeof(struct float_number));
    Initialize_Floating_Number(fn);
    Create_Bit_Representation(fn);
    Seperate_Floating_Number(fn);
    Generate_Sigificand_Number(fn);
    Print_Float_Number(fn);
    printf("Structure size: %d bytes\n", (int)sizeof(struct float_number));
    
    free(fn);
    return 0;


}
