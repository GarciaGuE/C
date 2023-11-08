#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//Function to convert text in an input file to uppercase and save it to an output file
void uppercaseSaveConverter(char *inputFile,char *outputFile){
	FILE *inputF, *outputF;
	int c;
	
	if((inputF=fopen(inputFile,"r"))==NULL){
		printf("Error opening the file %s\n",inputFile);
		exit(-1);
	}

	if((outputF=fopen(outputFile,"w"))==NULL){
		printf("Error opening the file %s\n",outputFile);
		exit(-1);
	}

	c=fgetc(inputF);
	
	while(c!=EOF){
		fputc(toupper(c),outputF);
		c=fgetc(inputF);
	}
	
	fclose(inputF);
	fclose(outputF);
}

int main(){
	char inputFile[256];
	char outputFile[256]="uppercase-";

	printf("Enter the name of the input file: ");
	scanf("%s",inputFile);
	
	strcat(outputFile,inputFile);
	
	uppercaseSaveConverter(inputFile,outputFile);
	
	return 0;
}
