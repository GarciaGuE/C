#include <stdio.h>

//If the value assigned to variable 'a' starts at address 1130 (hexadecimal), the value assigned to variable 'b' starts at 1134, and the value assigned to variable 'c' starts at 1138, then after executing all the statements:
float main(){
	float a=0.001;
	float b=0.003;
	float c, *pa, *pb;
	pa=&a;
	*pa=2*a;
	pb=&b;
	c=3*(*pb+*pa);

	// a) What value is represented by &a?
    printf("\nValue of &a: \n %p\n", &a);
    
    // b) What value is represented by &b?
    printf("\nValue of &b: \n %p\n", &b);
    
    // c) What value is represented by &c?
    printf("\nValue of &c: \n %p\n", &c);
    
    // d) What value is assigned to pa?
    printf("\nValue of pa: \n %p\n", pa);
    
    // e) What value is represented by *pa?
    printf("\nValue of pa: \n %f\n", *pa);
    
    // f) What value is represented by &(*pa)?
    printf("\nValue of &(*pa): \n %p\n", &(*pa));
    
    // g) What value is assigned to pb?
    printf("\nValue of pb: \n %p\n", pb);
    
    // h) What value is represented by *pb?
    printf("\nValue of *pb: \n %f\n", *pb);
    
    // i) What value is assigned to c?
    printf("\nValue of c: \n %f \n", c);
    
    return 0;
}
