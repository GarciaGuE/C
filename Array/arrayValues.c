#include <stdio.h>	
	
int main(){
	int x[8]={10, 20, 30, 40, 50, 60, 70, 80};

	// a) What is the meaning of x?
    printf("Value of x: \n %p\n", x);
    
    // b) What is the meaning of (x + 2)?
    printf("\nValue of (x+2): \n %p\n", (x+2));

	// c) What is the value of *x?
    printf("\nValue of *x: \n %i\n", *x);
    
    // d) What is the value of (*x+2)?
    printf("\nValue of (*x+2): \n %i\n", (*x+2));
    
    // e) What is the value of *(x+2)?
    printf("\nValue of *(x+2): \n %i \n", *(x+2));

	return 0;
}
