#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>


/*
 * The server provides the service of incrementing a number received from a client.
 */
int main(){
	/*---------------------------------------------------- 
        Socket descriptor and data buffer
    -----------------------------------------------------*/
	int ServerSocket;
	struct sockaddr_in Server;
	int count=0;

	/* -----------------------------------------------------
        Client Information
    ----------------------------------------------------- */
   	struct sockaddr_in Client;
	socklen_t ClientLength;

	/* --------------------------------------------------
        Open the Server socket
    ---------------------------------------------------*/
	ServerSocket=socket(AF_INET, SOCK_DGRAM, 0);
	if(ServerSocket==-1){
		printf("Cannot open the server socket\n");
		exit(-1);	
	}

	/* ------------------------------------------------------------------
        Fill in the fields of the server structure, required
        for the bind() function call.
    -------------------------------------------------------------------*/
	Server.sin_family=AF_INET;
	Server.sin_port=htons(2000);
	Server.sin_addr.s_addr=htonl(INADDR_ANY); 
	if(bind(ServerSocket, (struct sockaddr *)&Server, sizeof(Server))==-1){
		close(ServerSocket);
		exit(-1);
	}

  	/*----------------------------------------------------------------------
        For the client, we only need the size of its structure, the
        rest of the information (family, port, IP) will be provided
        by the recvfrom method when we receive a call from a client.
    ----------------------------------------------------------------------*/
	ClientLength=sizeof(Client);

	/*-------------------------------------------------------
        The server continuously waits for messages from clients
    -------------------------------------------------------- */
	while(1){
    	/* -----------------------------------------------------------------
            We wait for a call from any client
        -------------------------------------------------------------------*/
        int received=recvfrom(ServerSocket, &count, sizeof(count), 0, (struct sockaddr *)&Client, &ClientLength);

        /* -----------------------------------------------------------------
            Check if we have received any information
        -------------------------------------------------------------------*/
        if (received>0) {
            /*-----------------------------------------------------------------
                Increment the value sent by the client
            ------------------------------------------------------------------*/
            printf("Received %d, sending %d\n", count, count + 1);
            count++;

            /* ------------------------------------------------------------------
                Send the incremented number back to the client
            --------------------------------------------------------------------*/
            int sent=sendto(ServerSocket, &count, sizeof(count), 0, (struct sockaddr *)&Client, ClientLength);
        }
    }
	 close(ServerSocket);
	return 0;
}
