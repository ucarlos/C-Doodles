//--------------------------------------------------------------------------------------------------
// Created by Ulysses Carlos on 10/5/19 using Ulysses-H270-HD3.
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){
    char *source = calloc(50, sizeof(char));
    strncpy(source, "Test: ", 30);
    char *destin = "Noah is a massive faggot.";

    printf("Intial: ");
    puts(source);

    strncat(source + strlen(source), destin, 40);

    printf("Afterwords --> ");
    puts(source);



}

