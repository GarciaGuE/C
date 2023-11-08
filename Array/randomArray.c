#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// A software project requires working with arrays of random integers. To make access faster, they have decided to create two indexes that allow them to iterate only over elements divisible by 3 or odd elements. An index is an array of pointers that stores the addresses of the elements to be traversed. Write a program that:
// • Fills an array of integers with random numbers (within a user-defined range).
// • Prints the entire array.
// • Creates an index with the addresses of the odd elements in the original array.
// • Creates an index with the addresses of the elements divisible by 3 in the original array.
// • Prints, using the indexes, the odd elements and those divisible by 3. Implement at least the following functions: fillRandomArray, printArray, createOddIndex, createDivisibleIndices, printIndex.
void fillRandomArray(int *v, int n, int range){
	int i;
  	time_t t;
  	srand(time(&t));
  	for(i=0; i<n; i++) v[i]=rand()%(range+1);
}

void printArray(int *v, int n){
	int i;
    printf("Your random array is: \n |");
  	for(i=0; i<n; i++) printf(" %d |",v[i]);
}

void createOddIndex(int *v, int **ind, int n, int *nIndex){
  	int i;
  	*nIndex=0;
  	for(i=0; i<n; i++){
  		if(v[i]%2!=0){
  			ind[*nIndex]=&v[i];
      		(*nIndex)++;
    	}
  	}
}

void createDivisibleIndices(int *v, int **ind, int n, int *nIndex){
  	int i;
  	*nIndex=0;
  	for(i=0; i<n; i++){
		if(v[i]%3==0){
			ind[*nIndex]=&v[i];
			(*nIndex)++;
		}
  	}
}

void printIndex(int **ind, int nIndex){
  	int i;
  	printf("Index: \n |");
  	for(i=0; i<nIndex; i++) printf(" %d |", *(ind[i]));
}

void main(){
 	int n, range, nIndexImp, nIndexDiv;

    printf("How many elements should your array have?\n");
    scanf("%d", &n);
  	
	int v[n], *indImp[n], *indDiv[n];

  	printf("Enter the range: \n");
    scanf("%d", &range);

  	fillRandomArray(v,n,range);
  	printArray(v,n);
  	printf("\n");

  	createOddIndex(v,indImp,n,&nIndexImp);
  	printf("The odd numbers in your array are: \n");
  	printIndex(indImp, nIndexImp);
  	printf("\n");

  	createDivisibleIndices(v,indDiv,n,&nIndexDiv);
  	printf("The numbers divisible by 3 in your array are: \n");
  	printIndex(indDiv, nIndexDiv);
  	printf("\n");
}
