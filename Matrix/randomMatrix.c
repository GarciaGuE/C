#include <stdio.h>
#include <time.h>
#include <stdlib.h>

float **allocateMemory(int rows, int columns){
	float **matrix;
	matrix=(float**)malloc(rows*sizeof(float*));

	if(matrix==NULL){
		printf("Error: could not allocate memory");
		exit(-1);
	}

	for(int i=0; i<rows; i++)	matrix [i]=(float*)malloc(columns*sizeof(float));
	
	return(matrix);
}

void fillMatrix(float **matrix, int rows, int columns){
	for(int i=0; i<rows; i++)
		for(int j=0; j<columns; j++)	*(*(matrix+i)+j)=rand()%21;
}

void printMatrix(float **matrix, int rows, int columns){
	for(int i=0; i<rows; i++){
		printf("( ");
		for(int j=0; j<columns; j++)	printf("%f ", *(*(matrix+i)+j));
		printf(")\n");
	}
}

void freeMemory(float ***matrix, int rows){
	for(int i=0; i<rows; i++)	free((*matrix)[i]);
	free(*matrix);
	(*matrix)=NULL;
}

int main(){
	float **matrix;
	matrix=allocateMemory(2, 3);
	
	fillMatrix(matrix, 2, 3);
	printMatrix(matrix, 2, 3);	
	freeMemory(&matrix, 2);
	
	return 0;
}

