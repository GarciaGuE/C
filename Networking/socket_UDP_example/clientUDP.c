#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>

/* --------------------------------------------------------
 
 Sends a random number to the server, which returns the incremented number.

---------------------------------------------------------- */
int main(){
	/*---------------------------------------------------- 
        Socket descriptor and data buffer
    -----------------------------------------------------*/
	int ClientSocket;
	int Data;

   	/* -----------------------------------------------------
        Server Information
    ----------------------------------------------------- */
   	struct sockaddr_in Server;  
   	socklen_t ServerLength;
	
	/* --------------------------------------------------
        Open the client socket
    ---------------------------------------------------*/
	ClientSocket=socket(AF_INET, SOCK_DGRAM, 0);
	if(ClientSocket==-1){
		printf("Cannot open the client socket\n");
		exit(-1);	
	}
	
	/* -----------------------------------------------------
        We need a structure with server information to request a service.
    ----------------------------------------------------- */
	Server.sin_family=AF_INET;
	Server.sin_port=htons(2000);
	Server.sin_addr.s_addr=inet_addr("127.0.0.1");
	ServerLength=sizeof(Server);
	
	/*--------------------------------------------------------
        Generate a random number, which is sent to the server.
    -------------------------------------------------------- */
 	srand(time(NULL)); /* Seed for random numbers */
    Data=rand()%20;  /* Random number between 0 and 19 */
    printf("Sending %d\n", Data);

	/*----------------------------------------------------------
        Send a message to the server
    ----------------------------------------------------------*/
    int sent=sendto(ClientSocket, (char *)&Data, sizeof(Data), 0, (struct sockaddr *)&Server, ServerLength);
   	if(sent<0)
		printf("Error requesting the service\n");
    else{
		/*----------------------------------------------------------
            Wait for the server's response
        ---------------------------------------------------------- */ 
        int received=recvfrom(ClientSocket, (char *)&Data, sizeof(Data), 0, (struct sockaddr *)&Server, &ServerLength);
        if (received>0)
            printf("Received %d\n", Data);
        else
            printf("Error reading from the server\n");
    }
	close(ClientSocket);
	return 0;
}
