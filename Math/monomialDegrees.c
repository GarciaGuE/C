#include <stdio.h>
#include <math.h>

//A monomial (5x^3) can be represented in C using a structure with two integer fields: 
//coefficient and degree (e.g., coefficient = 5, degree = 3). A polynomial is a sequence of monomials with different degrees (5x^3 + 7x^2 + 4x^5).
struct Monomial{
	int coefficient;
	int degree;
};

void readMonomial(struct Monomial *m){
	printf("Enter the coefficient: ");
    scanf("%i", &m->coefficient);

    printf("Enter the degree: ");
    scanf("%i", &m->degree);
}

void printMonomial(struct Monomial m){
	printf("%ix^%i", m.coefficient, m.degree);
}

void maxMin(struct Monomial *m, int size, struct Monomial *max, struct Monomial *min){
	for(int i=0; i<size; i++){
		for (int j=i+1; j<size; j++){
			if((m+i)->degree<(m+j)->degree){
				struct Monomial aux=m[i];
				m[i]=m[j];
				m[j]=aux;
			}
		}
	}
	*max=m[0];
	*min=m[size-1];
}

int solveFunction(struct Monomial *m, int size, int val){
	int res=0;
	for(int i=0; i<size; i++)
		res+=(m+i)->coefficient*(pow((val), (m+i)->degree));

	return res;
}

int main(){
	int n, val;

    printf("Number of monomials: ");
    scanf("%d", &n);
	
	struct Monomial polynomial[n], max, min;
	
	for(int i=0; i<n; i++)
		readMonomial(polynomial+i);

   printf("Your polynomial is:\n");
	
	for(int j=0; j<n; j++){
		printMonomial(polynomial[j]);
		printf("\n\n");
	}
	
	maxMin(polynomial,n,&max,&min);
	printf("The monomial with the highest degree is: %d(x)^%d \n", max.coefficient, max.degree);
	printf("The monomial with the lowest degree is: %d(x)^%d\n", min.coefficient, min.degree);
	
    printf("\nEnter the value of x: ");
    scanf("%d", &val);

	printf("The result of '");
	
	for(int k=0; k<n; k++)
		printMonomial(polynomial[k]);

	printf("' with x=%d is %d\n", val, solveFunction(polynomial,n,val));
}
