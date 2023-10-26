#include<stdio.h>
#include<sys/time.h>
#include<sys/socket.h>

int main(){
	struct timeval timeout;
	fd_set readSet;
	int output;
	char str[60];

	//Initialize the timeval structure
	timeout.tv_sec=5;
	timeout.tv_usec=0;
	
	//Initialize the file descriptor set (fd_set)
	FD_ZERO(&readSet);
	FD_SET(0,&readSet);
	

	output=select(1,&readSet,NULL,NULL,&timeout);
	if(output==-1)
		printf("An error occurred in select.\n");
	else if(output==0)
		printf("Timeout expired\n");
	else{
		fgets(str,sizeof(str),stdin);
		printf("You have typed on the screen: %s\n",str);
	}
	return 0;
}
