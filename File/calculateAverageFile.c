#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Function to calculate the mean of even elements in a text file
float average(char *fileName){
        FILE *f;
        int sum=0,c=0;
        int num, end;
        float m=0;
        
        f=fopen(fileName,"r");
        if(f==NULL) {
                printf("Error: Could not open the file %s.\n",fileName);
                exit(-1);
        }
        
        end=fscanf(f,"%d",&num);
        
        while(end==1){
                if(num%2==0){
                        sum=sum+num;
                        c++;
                }
                end=fscanf(f,"%d",&num);
        }
        
        m=sum/c;
        
        fclose(f); 
        
        return m;
}

//Numbers in file.txt: 
// 1 
// 2 
// 3 
// 4 
int main(int argc,char *argv[]){
        if(argc!=2){
		printf("Incorrect syntax: %s <fileName>\n",argv[0]);
		exit(-1);
        }
        
        printf("The average of even elements in the file %s is: %f",argv[1],average(argv[1]));
        printf("\n");
	
        return 0;
}
