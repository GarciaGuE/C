#include <stdio.h>
#include <math.h>

//Write a function named "arrayStatistics" that receives an array of integers and calculates, 
//returning the results through pass-by-reference, the average, variance and standard deviation of the data in the array.
void arrayStatistics(float *v, int n, float *avg, float *variance, float *standardDeviation){
	float sum=0;
	for(int i=0; i<n; i++)
		sum+=*(v+i);
	*avg=sum/n;
	sum=0;
	for(int j=0; j<n; j++){	
		sum+=pow((*(v+j)-*avg),2);
	}
	*variance=sum/n;
	*standardDeviation=sqrt(*variance);
}

void writeArray(float *v, int n){
	for(int i=0; i<n; i++){
		printf("V[%i]:", i);
		scanf("%f", &(*(v+i)));
	}
}

void readArray(float *v, int n){
	for(int i=0; i<n; i++)
		printf("%f\n", *(v+i));
}

int main(){
	float v[5];
	writeArray(v, 5);
	readArray(v, 5);
	float avg, variance, standardDeviation;
	arrayStatistics(v, 5, &avg, &variance, &standardDeviation);
	printf("\nArray Statistics:\n Avg=%f \n Variance=%f \n standardDeviation=%f \n", avg, variance, standardDeviation);
	return 0;
}