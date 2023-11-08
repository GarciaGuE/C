#include <stdio.h>

//If the value assigned to i starts at address F9C (hexadecimal) and the value assigned to j starts at FE9, then after executing all the statements:
int main(){
	int i, j=25;
	int *pi, *pj;
	pj=&i;
	*pj=j+5;
	i=*pj+5;
	pi=pj;
	*pi=i+j;

 	// a) What value is represented by &i?
    printf("Value of &i: \n %p\n", &i);

    // b) What value is represented by &j?
    printf("\nValue of &j: \n %p\n", &j);
    
    // c) What value is assigned to pj?
    printf("\nValue of pj: \n %p\n", pj);
    
    // d) What value is assigned to *pj?
    printf("\nValue of *pj: \n %i\n", *pj);
    
    // e) What value is assigned to i?
    printf("\nValue of i: \n %i\n", i);
    
    // f) What value is represented by pi?
    printf("\nValue of pi: \n %p\n", pj);
    
    // g) What value is assigned to *pi?
    printf("\nValue of *pi: \n %i\n", *pi);
    
    // h) What value is represented by the expression (*pi + 2)?
    printf("\nValue of (*pi+2): \n %i \n\n", (*pi+2));

	return 0;
}
