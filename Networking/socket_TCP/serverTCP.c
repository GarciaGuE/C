#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
 * The server reads and displays on the screen the string sent by the client until it receives "FIN."
 */

int main(){
	/*---------------------------------------------------- 
		Socket descriptor and data buffer                
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[100];
	socklen_t from_len;
	struct hostent* host;

	/* --------------------------------------------------
		Open the socket 
	---------------------------------------------------*/
  	sd=socket(AF_INET, SOCK_STREAM, 0);
	if(sd==-1){
		perror("Unable to open the server socket.\n");
    	exit(1);	
	}

	sockname.sin_family=AF_INET;
	sockname.sin_port=htons(2000);
	sockname.sin_addr.s_addr=INADDR_ANY;
	
	if(bind(sd, (struct sockaddr*) &sockname, sizeof(sockname))==-1){
		perror("Error in bind operation");
		exit(1);
	}

   	/*---------------------------------------------------------------------
		We only need the size of the structure for the requests 
		we are going to accept. The rest of the information 
		(family, port, IP) will be provided by the method receiving 
		the requests.
   	----------------------------------------------------------------------*/
	from_len=sizeof(from);
	if(listen(sd,1)==-1){
		perror("Error in the listen operation.");
		exit(1);
	}

	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */
	while(1){
		if((new_sd = accept(sd, (struct sockaddr *)&from, &from_len))==-1){
			perror("Error accepting requests.");
			exit(1);
		}
		while(strcmp(buffer, "END")!=0){
			if(recv(new_sd, buffer, 100, 0) == -1)
				perror("Error in the recv operation.");	
				printf("Received message: \n%s\n", buffer );
		}

		close(new_sd);
	}

	close(sd);
	return 0;
}

