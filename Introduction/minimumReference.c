#include <stdio.h>

// Demonstrating the equivalence between functions that return a result and functions that use parameters by reference.
// a) First version: function named "minimum". It receives two integers, num1 and num2, passed by value. It returns the minimum of the two numbers, num1 and num2, passed as parameters.
int minimum(int num1, int num2);

// Second version: function named "minimum_reference". It receives two integers, num1 and num2, passed by value and another parameter called "result" of type int, but passed by reference. The function assigns the minimum value of num1 and num2 to the "result" variable.
void minimum_reference(int num1, int num2, int *result);

int main(){
	int a, b, c;
	printf("Enter a value for a: ");
	scanf("%i", &a);

	printf("\\nEnter a value for b: ");
	scanf("%i", &b);

	printf("\nThe minimum of the two is: %i \n ", minimum(a, b));

	printf("\nEnter a value for a: ");
	scanf("%i", &a);

	printf("\\nEnter a value for b: ");
	scanf("%i", &b);

	minimum_reference(a, b, &c);

	printf("\nThe minimum by reference of the two is: %i \n", c);

	return 0;
}

int minimum(int num1, int num2){
	int m=num1;
	
	if(num1>num2)	m=num2;
	if(num1==num2)	printf("\nThe numbers are equal.");

	return m;
}

void minimum_reference(int num1, int num2, int *result){
	if(num1>num2)	*result=num2;
	else	*result=num1;
	if(num1==num2)	printf("\nThe numbers are equal.");
}