#include <stdio.h>
#include <stdlib.h>

// Implement a function that allows you to multiply dynamic matrices.
float **allocateMatrix(int rows, int columns){
	float **matrix;
	matrix=(float**)malloc(rows*sizeof(float*));
	
	if(matrix==NULL){
		printf("Error: could not allocate memory");
		exit(-1);
	}
	
	for(int i=0; i<rows; i++)	matrix[i]=(float*)malloc(columns*sizeof(float));
	
	return(matrix);	
}

void fillMatrix(float **matrix, int rows, int columns){
	for(int i=0; i<rows; i++)
		for(int j=0; j<columns; j++){
			printf("\nM[%d][%d]: ", i, j);
			scanf("%f", &*(*(matrix+i)+j));
		}
}

void printMatrix(float **matrix, int rows, int columns){
	for(int i=0; i<rows; i++){
		printf("| ");
		for(int j=0; j<columns; j++){
			printf("%f ", *(*(matrix+i)+j));
		}
		printf("|\n");
	}
}

void freeMatrix(float ***matrix, int rows){
	for(int i=0; i<rows; i++)	free((*matrix)[i]);
	free(*matrix);
	(*matrix)=NULL;
}

float **multiplyMatrix(float **matrix, float **matrix2, int rows, int columns2, int columns){
	float **result;
	result=(float**)malloc(rows*sizeof(float*));
	if(result==NULL){
		printf("Error: could not allocate memory");
		exit(-1);
	}

	for(int i=0; i<rows; i++)
		result[i]=(float*)malloc(columns2 * sizeof(float));
	
	for(int i=0; i<rows; i++){
		for(int a=0; a<columns2; a++){
			float sum=0.0;
			for(int j=0; j<columns; j++){
				sum+=matrix[i][j] * matrix2[j][a];
			}
			result[i][a]=sum;
		}
	}

	return(result);
}

int main(){
	float **matrix, **matrix2, **result;
	
	matrix=allocateMatrix(2, 3);
	matrix2=allocateMatrix(3, 2);
	
	fillMatrix(matrix, 2, 3);
	fillMatrix(matrix2, 3, 2);
	
	printMatrix(matrix, 2, 3);
	printMatrix(matrix2, 3, 2);
	
	printf("\nResult:\n");
	result=multiplyMatrix(matrix, matrix2, 2, 2, 3);
	printMatrix(result, 2, 2);	
	
	freeMatrix(&matrix, 2);
	freeMatrix(&matrix2, 3);
	freeMatrix(&result, 3);
	
	return 0;
}
