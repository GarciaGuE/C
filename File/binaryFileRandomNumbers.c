#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Function to generate random numbers within a specified range
int generateRandomNumber(int upper,int lower){
	return (rand()%(upper-lower+1)+(lower));
}

void createFile(char *fileName, int numElements, int upper, int lower){
	FILE *f;
	int i;
	time_t t;
	srand((int)time(&t));
	
	f=fopen(fileName, "wb");
	if(f==NULL){
		printf("\nError: Could not create the file <%s>", fileName);
		exit(-1);
	}

	for(i=0; i<numElements; i++){
		int num=generateRandomNumber(upper, lower);
		fwrite(&num, sizeof(int), 1, f);
	}

	fclose(f);
}

int main(int argc,char *argv[]){
	if(argc!=5){
		printf("Incorrect syntax: %s <fileName> <numElements> <upper> <lower>\n",argv[0]);
		exit(-1);
	}
	
	int numElements, upper, lower;
	numElements=atoi(argv[2]);
	upper=atoi(argv[3]);
	lower=atoi(argv[4]);
	createFile(argv[1], numElements, upper, lower);
	
	return 0;
}
