#include "./common_header.h"
/*
 * Write a function with the following prototype:
 */
int tsub_ok(int x, int y);
/* This function should return 1 if the computation x-y does not overflow */
int tadd_ok(int x, int y);

/* 
 * Basically, take the tadd_ok function you wrote for Problem2_30.c, and adjust it so
 * that you can handle the Tmin case (i.e. the lowest value for a 32bit signed integer)
 */
int main(void){
    int a, b;
    puts ("Enter two integers:");
    scanf("%d", &a);
    b = INT_MIN;
    printf("Testing whether %d and %d can be added without overflow...\n",
            a, b);
    printf("x          y          \tOverflow?\n");
    printf("%10d %10d\t", a, b);
    printf((tsub_ok(a, b) ? "No.\n" : "Yes.\n"));

    return 0;
}

int tsub_ok(int x, int y){
    if (y == INT_MIN) // I think this is a BAD idea when x = INT_MAX
        return tadd_ok(x - 1, y + 1);
    else
        return tadd_ok(x, -y);
 
}

int tadd_ok(int x, int y){
    int sum = x + y;
    // Check for Negative overflow:
    int pos_overflow = (x > 0) && (y > 0) && (sum < 0);
    int neg_overflow = (x < 0) && (y < 0) && (sum >= 0);
    
    return !(pos_overflow || neg_overflow);

}
