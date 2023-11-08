#include <stdio.h>
#include <stdlib.h>

//Function that, given a dynamic array, its length and an integer (num), returns two dynamic arrays.
//One will contain elements greater than num, and the other will contain elements less than or equal to num.
void fillArray(int* v, int length){
	int x;
	
  	for(int i=0;i<length;i++){
		printf("Enter the element %i: ", i);
    	scanf("%d", &x);
		v[i]=x;
  	}

	for(int i=0;i<length;i++)
		printf("V[%d] = %d\n",i,*(v+i));
}

void allocateArrays(int** v1, int** v2, int length){
  	if((*v1=(int*)malloc(length*sizeof(int)))==NULL){
		printf("Error allocating memory.\n");
		exit(-1);
  	}
  	if((*v2=(int*)malloc(length*sizeof(int)))==NULL){
		printf("Error allocating memory.\n");
		exit(-1);
  	}
}

void separateElements(int* v, int length, int n, int* nEle1, int* nEle2, int** v1, int** v2){
  	int count1=0, count2=0;
  	for(int i=0;i<length;i++){
  		if(v[i]>n){
			(*v1)[count1]=v[i];
			count1++;
    	}
		else{
			(*v2)[count2]=v[i];
			count2++;
     	}
		
     	*nEle1=count1;
     	*nEle2=count2;
  	}

  	if((*v1=(int*)realloc(*v1,(*nEle1)*sizeof(int)))==NULL){
		printf("Error changing the array.\n");
		exit(-1);
  	}

  	if((*v2=(int*)realloc(*v2,(*nEle2)*sizeof(int)))==NULL){
		printf("Error changing the array.\n");
		exit(-1);
  	}
}

void display(int *v1, int *v2, int nEle1, int nEle2){
  	
    printf("V1 =");
	for(int i=0;i<nEle1;i++)	printf(" %d", v1[i]);

	printf("\n");
	printf("V2 =");
  	
	for(int j=0;j<nEle2;j++)	printf(" %d",v2[j]);
	
	printf("\n");
}

int main(){
  	int n, length, nEle1, nEle2;

  	printf("Enter the array length: ");
    scanf("%d", &length);
  	
	int v[length];
  	int *v1, *v2;
	
	allocateArrays(&v1,&v2,length);
  	fillArray(v,length);
  	
	printf("Enter a number: ");
  	scanf("%d",&n);
  	
	if(n<0){
		printf("Invalid number.\n");
		exit(-1);
  	}
  	
	separateElements(v,length,n,&nEle1,&nEle2,&v1,&v2);
  	display(v1,v2,nEle1,nEle2);
  	
	free(v1);
  	free(v2);
	
	return 0;
}
