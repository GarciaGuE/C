#include <stdio.h>
#include <string.h>

// Design a recursive function to count the number of times a character 'x' appears in the string 'str'.
int countCharacters(char *str, char *x, int size){
	if(size==0){
		if(str[size]==x[0])	return 1;
		else	return 0;
	}
	if(str[size]==x[0])	return 1+countCharacters(str, x, size-1);
	else	return 0+countCharacters(str, x, size-1);
}

int main(){
	char str[200], x[10];
	int count;
	
	printf("Enter a string: ");
	fgets(str, 200, stdin);
	
	printf("Enter the character to count: ");
	scanf("%s", x);
	
	int size=strlen(str);
	count=countCharacters(str, x, size);
	
	printf("The character '%s' appears %d times in the string.\n", x, count);
	
	return 0;
}
