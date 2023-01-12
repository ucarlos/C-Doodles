/* -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 08/29/2019
 *
 * Basically, just an complete implementation of Problem 5 on Exam 0 in 
 * Big Data Programming.
 *
 * This is what I should have written on the exam (And realized just after
 * the exam). That would be why I got a 85 on the exam.
 * -----------------------------------------------------------------------------
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#define STR_SIZE (100)

bool ischarnum(char c){
	return ('0' <= c && c <= '9') ? true : false;
}	


bool checkstring(const char *string){
	bool check; int digits = 0;
	for (const char *p = string; *p; p++){
		check = ischarnum(*p);
		if (check) digits++;
	}		

	return (!digits)? false : true;
}	


int main(void){
	char *string = calloc(STR_SIZE, sizeof(char));
	puts("Please enter a String:");
	fgets(string, STR_SIZE, stdin);
	// Some hack from Stackoverflow that handles newline appended to string:
	// Link if you're interested: https://stackoverflow.com/a/28462221
	string[strcspn(string, "\n")] = '\0';
	bool result = checkstring(string);
	printf("Does \"%s\" have digits? : ", string);
	printf((result)? "True" : "False");
	puts("");
	return 0;

}	
