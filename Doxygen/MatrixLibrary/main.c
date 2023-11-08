/**
@file main.c
@brief Program body where user input is obtained, and results from the functions are returned.
*/
#include "functions.h"
int main(){
	int** matrix;
	int rows=0;
	int columns=0;
	int div;
	int sum;
	
	printf("\nEnter the number of rows for the matrix: ");
	scanf("%i", &rows);
	
	printf("\nEnter the number of columns for the matrix: ");
	scanf("%i", &columns);
	
	matrix=allocateMatrix(rows, columns);
	
	printf("\nEnter the elements of your matrix: ");
	fillMatrix(matrix, rows, columns);
	
	printMatrix(matrix, rows, columns);
	countDivisibles(matrix, rows, columns, &div, &sum);
	
	printf("\nThe number of elements divisible by 3 is: %i", div);  
	printf("\nThe sum of elements divisible by 3 is: %i\n", sum);  
	
	freeMatrix(&matrix, rows);
	
	return 0;
}
