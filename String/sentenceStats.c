#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Program that reads a sentence and, from it, creates a dynamic array of strings with the different words in the sentence. Based on this array, the program should:
// - Calculate the average length of the words in the sentence, as well as the longest and shortest lengths (using pass-by-reference).
// - Build a dynamic array with the frequency of appearance of each length.
void readSentence(char *res){
  	scanf("%[^\n]%*c", res);
  	strcat(res,"\n");
}

char **separeWords(char *sentence, int *numWords){
  	int aux=0, spaceCount=0, prevSpace=-2, size=strlen(sentence);
  	*numWords=1;
  	char **words;
  	
	for(int i=0; i<size; i++){
  		if(sentence[i]==32||sentence[i]=='\n'){
			if(aux==0){
				words=(char**)calloc((*numWords),sizeof(char*));
				aux=1;
			}
       		else{
         		(*numWords)++;
         		words=(char**)realloc(words, (*numWords)*sizeof(char*));
       		}
			
			spaceCount=prevSpace+2;
			prevSpace=i-1;
			int wordsize=(prevSpace-spaceCount+1);
			words[(*numWords)-1]=(char*)calloc(wordsize+1,sizeof(char));
			
			for(int j=0; j<wordsize; j++)
				words[(*numWords)-1][j]=sentence[spaceCount+j];

			words[(*numWords)-1][wordsize]='\0';
		}
  	}

  	return words;
}

void readWords(int numWords, char **words){
  	for(int i=0; i<numWords; i++)	printf("%s\n",words[i]);
}

void wordStatistics(int numWords, char **words, float *average, int *longest, int *shortest){
  	*average=0,*longest=strlen(words[0]), *shortest=strlen(words[0]);
  	for(int i=0; i<numWords; i++){
		int aux=strlen(words[i]);
		(*average)+=aux;

		if(*longest<aux)
			*longest=aux;

		if(*shortest>aux)
			*shortest=aux;
  	}

  	*average=(*average)/numWords;
}

int *frequencyArray(int numWords, char **words, int longest){
  	int *res=(int*)calloc(longest, sizeof(int));
  	
	for(int i=0; i<numWords; i++){
   		int size=strlen(words[i]);
    	res[size]++;
  	}

	return res;
}

void printArray(int *v,int n){
  	for(int i=1; i<n+1; i++){
		printf("|%d= '%d' ",i,v[i]);
		printf("|\n");
	}
}

int main(){
  	char sentence[500];
	printf("Enter your sentence: ");
  	
	readSentence(sentence);
  	printf("%s",sentence);
  	
	int numWords, longest, shortest;
  	float average;
  	char **words=separeWords(sentence, &numWords);
  	
	readWords(numWords,words);
  	wordStatistics(numWords, words, &average, &longest, &shortest);
  	printf("%.2f %d %d\n",average,longest,shortest);
  	
	int *freqArray=frequencyArray(numWords, words, longest);
  	
	printArray(freqArray, longest);
	
	return 0;
}
