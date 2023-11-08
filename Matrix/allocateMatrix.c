#include <stdio.h>
#include <stdlib.h>

// Suppose a dynamic matrix (float ** table) with 2x3 elements, with the following values: { {1.1, 1.2, 1.3}, {2.1, 2.2, 2.3} }
float** allocateMatrix(int rows, int columns){
	float **matrix;
	matrix=(float**)malloc(rows*sizeof(float*));
	
	if(matrix==NULL){
		printf("Error: Memory allocation failed");
		exit(-1);
	}
	
	for(int i=0; i<rows; i++)
		matrix[i]=(float*)malloc(columns*sizeof(float));
	
	return(matrix);	
}

void fillMatrix(float** matrix, int rows, int columns){
	for(int i=0; i<rows; i++){
		for(int j=0; j<columns; j++){
			printf("M[%d][%d]: ", i, j);
			scanf("%f", &*(*(matrix+i)+j));
		}
	}
}

void printMatrix(float** matrix, int rows, int columns){
	for(int i=0; i<rows; i++){
		printf("( ");
		for(int j=0; j<columns; j++)
			printf("%f ", *(*(matrix+i)+j));
		printf(")\n");
	}
}

void freeMatrix(float*** matrix, int rows){
	for(int i=0; i<rows; i++)
		free((*matrix) [i]);

	free(*matrix);
	(*matrix)=NULL;
}

int main(){
	float** matrix;
	
	matrix=allocateMatrix(2, 3);
	fillMatrix(matrix, 2, 3);
	printf("\n");
	printMatrix(matrix, 2, 3);	
	freeMatrix(&matrix, 2);
	
	return 0;
}




