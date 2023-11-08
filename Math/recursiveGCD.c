#include <stdio.h>
#include <stdlib.h>

// Recursive solution that calculates the Euclidean algorithm, used to find the greatest common divisor of two integers. 
// The Euclidean algorithm is described as follows:
// gcd(x, y)=x, if y=0
// gcd(x, y)=gcd(y, mod(x, y)), if y>0 and x>=y
int gcd(int x, int y){
  if(y==0)  return x;
  else   return gcd(y, x%y);
}

int main (int argc, char *argv[]) {
   int x,y;
   int GCD;

   if(argc!=3) {
      printf("Error when executing, please write: %s <num X> <num Y> \n",argv[0]);
      exit(-1);
   }

   x=atoi(argv[1]);
   y=atoi(argv[2]);
   GCD=gcd(x,y);

   printf("The greatest common divisor of %d and %d is %d \n", x, y, GCD);
   
   return 0;
}



