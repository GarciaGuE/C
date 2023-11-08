#include <stdio.h>
#include <stdlib.h>

//Recursive function that calculates integer division of two numbers using the repeated subtraction method.
int integerDivision(int dividend, int divisor){
    if(divisor>dividend)    return 0;
    else    return 1+integerDivision(dividend-divisor, divisor);
}

void main(int argc, char *argv[]){
    int x,y;
    
    if(argc!=3){
        printf("Error in syntax: ./%s <dividend> <divisor>", argv[0]);
    }
    
    x=atoi(argv[1]);
    y=atoi(argv[2]);
    
    printf("The integer division of %d by %d is %d\n", x, y, integerDivision(x,y));
}
