#include <stdio.h>
#include <math.h>

float fx(float val){
    return (3*pow(2.71828,val)-2*val);
}

float gx(float val){
    return ((-val)*sin(val)+1.5);
}

float zx(float val){
    return (pow(val,3)-2*val+1);
}

float calculateAverage(float val, float (*p) (float)){
    float sumValue=0, sumFunction=0;

    for(float i=0.2; i<=val; i+=0.2){
        sumFunction+=p(i);
        sumValue+=i;
    }

    return sumFunction/sumValue;
}

int main(){
    int opt;
    float x, (*p) (float); //Function pointer

    printf("Enter a value: ");
    scanf("%f",&x);
    getchar();

    printf("\nChoose the function to evaluate:\n");
    printf("    1) f(x)=3*e^x-2x\n");
    printf("    2) g(x)=-x*sin(x)+1.5\n");
    printf("    3) z(x)=x^3-2x+1\n");
    printf("Enter your choice: ");
    scanf("%d",&opt);

    switch(opt){
        case 1:
            p=&fx;
            printf("\nThe function value is: %f\n", p(x));
            printf("\nThe average value of the selected function in the interval [0, %.2f] with 0.2 increment is: %f\n", x, calculateAverage(x, p));
        break;

        case 2:
            p=&gx;
            printf("\nThe function value is: %f\n", p(x));
            printf("\nThe average value of the selected function in the interval [0, %.2f] with 0.2 increment is: %f\n", x, calculateAverage(x, p));
        break;

        case 3:
            p=&zx;
            printf("\nThe function value is: %f\n", p(x));
            printf("\nThe average value of the selected function in the interval [0, %.2f] with 0.2 increment is: %f\n", x, calculateAverage(x, p));
        break;

        default:
            printf("Unrecognized function choice.\n");
    }
}
