
//-----------------------------------------------------------------------------
// Created by ulysses on 12/31/19.
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void){
    const int size = 10;
    int *list = calloc(size, sizeof(int));

    for (int i = 0; i < size; i++){
        list[i] = i;
        printf("%d ", list[i]);
    }

}