#include <stdio.h>
#include <ctype.h>

// Program that uses functions and pointer arithmetic to:
// • Read a array of elements of type double (readArray).
// • Print the array's data on the screen (printArray).
// • Sum the elements greater than zero in the array (sumArray).
void readArray(double array[], int n){
	for(int i=0; i<n; i++){
		printf("Enter the element of the array at position %i: ", i);
		scanf("%lf", &array[i]);
	}
}

void printArray(double array[], int n){
	for(int i=0; i<n; i++)
		printf("Position[%i]=%lf\n", i, array[i]);
}

void sumArray(double array[], int n, double *sum){
	for(int i=0; i<n; i++)
		if(array[i]>0)
			*sum=*sum+array[i];
}

int main(){
	int n=0;

	printf("Enter the number of elements in the array: ");
    scanf("%i", &n);

	double array[n];
	printf("\n");
	readArray(array, n);
	printf("\n");
	printArray(array, n);
	printf("\n");
	double sum=0;
	sumArray(array, n, &sum);
	printf("The sum of elements greater than 0 is: %lf\n", sum);
	
	return 0;
}
