#include <stdio.h>

//Program that prints the size of the following variable types
int main(){
	int a, *b, **c;
	double d, *e, **f;
	char g, *h, **i;
	printf("Size of a, b, and c: %lu, %lu, %lu\n", sizeof(a), sizeof(*b), sizeof(**c));
	printf("Size of d, e, and f: %lu, %lu, %lu\n", sizeof(d), sizeof(*e), sizeof(**f));
	printf("Size of g, h, and i: %lu, %lu, %lu\n", sizeof(g), sizeof(*h), sizeof(**i));
	return 0;
}
