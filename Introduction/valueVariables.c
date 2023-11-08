#include <stdio.h>

//Value of each variable
int main(){
	//Pointer with no assigned value
	int *px;
	printf("Value of px: \n %p\n", px);

	//Variables with no assigned values 
	float a=0, b=0;
	printf("\nValue of a and b: \n %f \n %f\n", a, b);

	//Pointers with no assigned values, except for the last one with the value of 'a' assigned
	float *pa=&a, *pb;
	
	printf("\nValue of pa and pb: \n %p \n %p\n", pa, pb);
	a=-0.167;				
	printf("\nValue of a: \n %f\n", a);
	printf("\nValue of pa: \n %p\n", pa);
	
	char c1=' ', c2=' ', c3=' ';
	printf("\nValue of c1, c2 and c3: \n %c \n %c \n %c\n", c1, c2, c3);
	
	char *pcl=0, *pc2=0, *pc3=&c1;
	printf("\nValue of pcl, pc2 and pc3: \n %p \n %p \n %p\n", pcl, pc2, pc3);
	
	return 0;
}
