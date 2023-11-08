#include <stdio.h>
#include <string.h>


// Program that allows determining if one string is a prefix or a suffix of another. Use the `strstr` function from the <string.h> library to implement:
// • A function which checks if a string is a prefix of another. The function returns 1 if it's a prefix and 0 otherwise.
// • A function which checks if a string is a suffix of another. The function returns 1 if it's a suffix and 0 otherwise.
int isPrefix(char *str, char *prefix){
   	char *pos=strstr(str, prefix);
   	int i,size_prefix=strlen(prefix);
   	if(pos!=NULL){
		for(i=0;i<size_prefix;i++)
			if(str[i]!=prefix[i])
				return 0;
		return 1;
   	}
   	return 0;
}

int isSuffix(char *str, char *suffix){
  	int i, size_suffix=strlen(suffix), size_str=strlen(str);
   	char *pos=strstr(str, suffix);
	if(pos!=NULL){
		for(i=(size_str);i>(size_str-size_suffix);i--)
				if(str[i]!=suffix[i-(size_str-size_suffix)])
					return 0;
		return 1;
	}
   	return 0;
}

int main(){
	char str1[100], prefix[100], str2[100], suffix[100];

   	printf("Enter a string (without spaces): ");
   	scanf("%s", str1);
   	
	printf("Enter another string to check if it's a prefix or not: \n");
    scanf("%s", prefix);
   	
	if(isPrefix(str1, prefix)==1)
      	printf("The entered string is a prefix.\n");
   	else
    	printf("The entered string is not a prefix.\n");

   	printf("Enter a string: ");
  	scanf("%s", str2);
  	
	printf("Enter another string to check if it's a suffix or not: \n");
    scanf("%s", suffix);

  	if(isSuffix(str2, suffix)==1)
      	printf("The entered string is a suffix.\n");
  	else
  		printf("The entered string is not a suffix.\n");


	return 0;
}
