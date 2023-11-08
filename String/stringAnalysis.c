#include <stdio.h>
#include <string.h>
#include <ctype.h>

//A string in C is an array of characters terminated with a special character ('\0').
//This character marks the end of the string and is used by string functions. 
//Keeping this in mind, code a function named "stringStatistics" that receives a string and calculates, returning through pass-by-reference,
// the number of digits, uppercase letters, lowercase letters and spaces in the string. Implement a program to test the previous function.
//Use functions from the <ctype.h> library to determine if a character is a digit, uppercase, etc.
void stringStatistics(char *str, int *numDigits, int *numUppercase, int *numLowercase, int *numSpaces){
	for(int i=0; str[i]!='\0'; i++){
		if(isspace(str[i]))
			(*numSpaces)++;
		if(isdigit(str[i]))
			(*numDigits)++;
		if(isupper(str[i]))
			(*numUppercase)++;
		if(islower(str[i]))
			(*numLowercase)++;
	}
}

int main(){
	char str[100];
	int numDigits=0;
	int numUppercase=0;
	int numLowercase=0;
	int numSpaces=0;

	printf("Enter your string: ");
	gets(str);

	stringStatistics(str, &numDigits, &numUppercase, &numLowercase, &numSpaces);
	printf("\nString Statistics: \n Number of digits=%d \n Number of uppercase letters=%d \n Number of lowercase letters=%d \n Number of spaces=%d \n", numDigits, numUppercase, numLowercase, numSpaces);
	
	return 0;
}

