#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>


int main(){
	/*---------------------------------------------------- 
		Socket descriptor and data buffer               
	-----------------------------------------------------*/
	int sd;
	struct sockaddr_in sockname;
	char buffer[250];
	socklen_t len_sockname;
    fd_set readfds, auxfds;
   	int output;
    int end=0;

	/* --------------------------------------------------
		Open the socket
	---------------------------------------------------*/
  	sd=socket (AF_INET, SOCK_STREAM, 0);
	if(sd==-1){
		perror("Unable to open the client socket.\n");
    	exit(1);	
	}

	/* ------------------------------------------------------------------
		Fill the fields of the structure with the 
		server's IP and the service port we're requesting
	-------------------------------------------------------------------*/
	sockname.sin_family=AF_INET;
	sockname.sin_port=htons(2000);
	sockname.sin_addr.s_addr=inet_addr("127.0.0.1");

	/* ------------------------------------------------------------------
		Request the connection with the server
	-------------------------------------------------------------------*/
	len_sockname=sizeof(sockname);
	if(connect(sd, (struct sockaddr* )&sockname, len_sockname)==-1){
		perror("Connection error.");
		exit(1);
	}

    //Initialize the data structures
    FD_ZERO(&auxfds);
    FD_ZERO(&readfds);
    FD_SET(0,&readfds);
    FD_SET(sd,&readfds);

	/* ------------------------------------------------------------------
		Transmit the information
	-------------------------------------------------------------------*/
	while(end==0){
        auxfds=readfds;
        output=select(sd+1,&auxfds,NULL,NULL,NULL);

        //Message from the server
        if(FD_ISSET(sd, &auxfds)){
            bzero(buffer,sizeof(buffer));
            recv(sd,buffer,sizeof(buffer),0);
            printf("\n%s\n",buffer);
            if(strcmp(buffer,"Too many connected clients.\n")==0)
                end=1;
            if(strcmp(buffer,"Server disconnected.\n")==0)
                end=1;
        }
        else{
            //Input from the keyboard
            if(FD_ISSET(0,&auxfds)){
                bzero(buffer,sizeof(buffer));   
                fgets(buffer,sizeof(buffer),stdin);
                if(strcmp(buffer,"EXIT\n")==0)
                    end=1;
                send(sd,buffer,sizeof(buffer),0);
            }
        }	
    }

    close(sd);
    return 0;
}