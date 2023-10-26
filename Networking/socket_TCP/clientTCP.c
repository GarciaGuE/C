#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/* The client sends a string of text to the server until it sends the string "END" */

int main(){
	/*---------------------------------------------------- 
		Socket descriptor and data buffer               
	-----------------------------------------------------*/
	int sd;
	struct sockaddr_in sockname;
	char buffer[100];
	socklen_t len_sockname;

	/* --------------------------------------------------
		Open the socket
	---------------------------------------------------*/
  	sd=socket (AF_INET, SOCK_STREAM, 0);
	if(sd ==-1){
		perror("Unable to open the client socket.\n");
    	exit (1);	
	}

	/* ------------------------------------------------------------------
		Fill in the structure fields with the server's 
		IP and the service port we are requesting
	-------------------------------------------------------------------*/
	sockname.sin_family=AF_INET;
	sockname.sin_port=htons(2000);
	sockname.sin_addr.s_addr=inet_addr("127.0.0.1");
	
	/* ------------------------------------------------------------------
		Request the connection with the server
	-------------------------------------------------------------------*/
	len_sockname=sizeof(sockname);
	if(connect(sd, (struct sockaddr *)&sockname, len_sockname)==-1){
		perror("Connection error.");
		exit(1);
	}

	/* ------------------------------------------------------------------
		Transmit the information
	-------------------------------------------------------------------*/
	while(strcmp(buffer, "END")!=0){
		puts("Enter the message to transmit:");
		gets(buffer);
		if(send(sd,buffer,100,0)==-1)
			perror("Error sending data.");
	}

	close(sd);
	return 0;
}
		

