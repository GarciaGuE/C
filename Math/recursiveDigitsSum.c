#include <stdio.h>

//Recursive function to sum the digits of a number.
int sumOfDigits(int n){
  	if(n<10)	return n;
  	else	return n%10+sumOfDigits(n/10);
}

int main(){
	int n;
	
	printf("Enter a number to calculate the sum of its digits: ");
	scanf("%d",&n);
	
	int sum=sumOfDigits(n);
	
	printf("The sum of the digits in %d is %d.\n", n, sum);
	return 0;
}
