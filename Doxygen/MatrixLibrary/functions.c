/**
@file functions.c
@brief Functions used in the main program (explained in "functions.h")
*/
#include "functions.h"

int	**allocateMatrix(int rows, int columns){
	int **matrix;
	matrix=(int**)malloc(rows*sizeof(int*));
	
	if(matrix==NULL){
		printf("Error: Failed to allocate memory");
		exit(-1);
	}
	
	for(int i=0; i<rows; i++)	matrix[i]=(int*)malloc(columns*sizeof(int));

	
	return(matrix);	
}

void fillMatrix(int **matrix, int rows, int columns){
	for(int i=0; i<rows; i++)
		for(int j=0; j<columns; j++){
			printf("\nM[%d][%d]: ", i, j);
			scanf("%i", &*(*(matrix+i)+j));
		}
}

void printMatrix(int **matrix, int rows, int columns){
	for(int i=0; i<rows; i++){
		printf("( ");
		for(int j=0; j<columns; j++){
			printf("%i ", *(*(matrix+i)+j));
		}
		printf(")\n");
	}
}

void countDivisibles(int **matrix, int rows, int columns, int *d, int *sum){
	*d=0;
	*sum=0;
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			if((matrix[i][j]%3)==0){
				(*d)++;
				(*sum)+=matrix[i][j];
			}
		}
	}
}

void freeMatrix(int ***matrix, int rows){
	for(int i=0; i<rows; i++)	free((*matrix)[i]);
	free(*matrix);
	(*matrix)=NULL;
}
