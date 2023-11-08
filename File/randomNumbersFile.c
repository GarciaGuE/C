#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Function to generate a random integer within a specified range
int generateRandomNumber(int upper,int lower){
	return (rand()%(upper-lower+1)+(lower));
}

void createFile(char *fileName, int numElements, int upper, int lower){
	FILE *f;
	int i;
	time_t t;
	srand((int)time(&t));
	f=fopen(fileName, "w");
	
	if(f==NULL){
		printf("\nError: Could not create the file <%s>", fileName);
		exit(-1);
	}

	for(i=0; i<numElements; i++)
		fprintf(f, "%i\n", generateRandomNumber(upper, lower));

	fclose(f);
}

int main(){
	char fileName[64];
	int numElements, upper, lower;

	printf("Enter the name of the file to create: ");
	scanf("%s", fileName);
	
	printf("Enter the number of elements for the file: ");
	scanf("%i", &numElements);
	
	printf("Enter the upper bound: ");
	scanf("%i", &upper);
	
	printf("Enter the lower bound: ");
	scanf("%i", &lower);
	
	createFile(fileName, numElements, upper, lower);
	
	return 0;
}
