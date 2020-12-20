//--------------------------------------------------------------------------------------------------
// Created by Ulysses Carlos on 10/16/19 using Ulysses-H270-HD3.
//--------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#define MAX_LENGTH (100)

int word_count(char *string){
    int wc = 0;
    int length = 0;
    for (char *p = string; *p; p++, length++){
        if ((*p) == ' ' || (*p) == '\n')
            wc = (length > 0 && (*(p - 1) != ' '))?
				wc + 1 : wc;
    }

    return wc;
}


int main(void){
    char *string = calloc(MAX_LENGTH, sizeof(char));
    puts("Please enter a string:");
    fgets(string, MAX_LENGTH, stdin);
    fputs(string, stdout);
    int result = word_count(string);
    printf("Word Count: %d\n", result);

	free(string);

}

