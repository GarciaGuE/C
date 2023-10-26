#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include<signal.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>


#define MSG_SIZE 250
#define MAX_CLIENTS 50


/*
 * The server provides a chat service.
 */

void signalHandler(int signum);
void exitClient(int socket, fd_set * readfds, int* numClients, int arrayClients[]);


int main(){
	/*---------------------------------------------------- 
		Socket descriptor and data buffer               
	-----------------------------------------------------*/
	int sd, new_sd;
	struct sockaddr_in sockname, from;
	char buffer[MSG_SIZE];
	socklen_t from_len;
    fd_set readfds, auxfds;
    int output;
    int arrayClients[MAX_CLIENTS];
    int numClients=0;
    
    //Counters
    int i,j,k;
    int received;
    char identifier[MSG_SIZE];
    int on, ret;

	/* --------------------------------------------------
		Open the socket
	---------------------------------------------------*/
  	sd=socket(AF_INET, SOCK_STREAM, 0);
	if(sd==-1){
		perror("Unable to open the server socket.\n");
    	exit(1);	
	}

    // Enable a socket property to allow other sockets to reuse any port we bind to.
    // This allows running the same program multiple times and binding it to the same port.
    // Otherwise, we would have to wait for the port to become available (TIME_WAIT in TCP).
    on=1;
    ret=setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
	sockname.sin_family=AF_INET;
	sockname.sin_port=htons(2000);
	sockname.sin_addr.s_addr=INADDR_ANY;
	
    if(bind (sd, (struct sockaddr*) &sockname, sizeof(sockname))==-1){
		perror("Error in the bind operation.");
		exit(1);
	}

   	/*---------------------------------------------------------------------
		We only need the size of the structure for the requests 
        we accept. The rest of the information (family, port, IP) 
        will be provided by the method that receives the requests.
   	----------------------------------------------------------------------*/
	from_len=sizeof(from);
	if(listen(sd,1)==-1){
		perror("Error in the listen operation.");
		exit(1);
	}

	//Initialize the fd_set data structures
    FD_ZERO(&readfds);
    FD_ZERO(&auxfds);
    FD_SET(sd,&readfds);
    FD_SET(0,&readfds);

    //Capture the SIGINT signal (Ctrl+C)
    signal(SIGINT,signalHandler);

	/*-----------------------------------------------------------------------
		The server accepts a request
	------------------------------------------------------------------------ */
    while(1){
        //We expect to receive messages from clients (new connections or messages from already connected clients)
        auxfds=readfds;            
        output=select(FD_SETSIZE,&auxfds,NULL,NULL,NULL);            
        if(output>0){                              
            for(i=0; i<FD_SETSIZE; i++){

                //Find the socket through which communication has been established
                if(FD_ISSET(i, &auxfds)) {   
                    if(i==sd){
                        if((new_sd=accept(sd, (struct sockaddr *)&from, &from_len))==-1)
                            perror("Error accepting requests.");
                        else{
                            if(numClients<MAX_CLIENTS){
                                arrayClients[numClients]=new_sd;
                                numClients++;
                                FD_SET(new_sd,&readfds);
                                strcpy(buffer, "Welcome to the chat.\n");
                                send(new_sd,buffer,sizeof(buffer),0);
                                for(j=0; j<(numClients-1);j++){
                                    bzero(buffer,sizeof(buffer));
                                    sprintf(buffer, "New Client connected: %d\n",new_sd);
                                    send(arrayClients[j],buffer,sizeof(buffer),0);
                                }
                            }
                            else{
                                bzero(buffer,sizeof(buffer));
                                strcpy(buffer,"Too many clients connected.\n");
                                send(new_sd,buffer,sizeof(buffer),0);
                                close(new_sd);
                            }                        
                        } 
                    }
                    else if(i==0){
                        //Information has been entered from the keyboard
                        bzero(buffer, sizeof(buffer));
                        fgets(buffer, sizeof(buffer),stdin);

                        //Controlar si se ha introducido "EXIT", cerrando todos los sockets y finalmente saliendo del servidor. (implementar)
                        if(strcmp(buffer,"EXIT\n")==0){
                            for(j=0; j<numClients; j++){
                                bzero(buffer, sizeof(buffer));
                                strcpy(buffer,"Server disconnection.\n"); 
                                send(arrayClients[j],buffer, sizeof(buffer),0);
                                close(arrayClients[j]);
                                FD_CLR(arrayClients[j],&readfds);
                            }

                            close(sd);
                            exit(-1);
                        }
                        //Messages to be sent to clients (to be implemented)
                    } 
                    else{
                        bzero(buffer,sizeof(buffer));
                        received=recv(i,buffer,sizeof(buffer),0);
                        if(received > 0){                                
                            if(strcmp(buffer,"EXIT\n")==0){                                  
                                exitClient(i,&readfds,&numClients,arrayClients);                                    
                            }
                            else{                                   
                                sprintf(identifier,"%d: %s",i,buffer);
                                bzero(buffer,sizeof(buffer));
                                strcpy(buffer,identifier);                                   
                                for(j=0; j<numClients; j++)
                                    if(arrayClients[j] !=i)
                                        send(arrayClients[j],buffer,sizeof(buffer),0);                             
                            }                                                                                               
                        }

                        //If the client entered Ctrl+C
                        if(received==0){
                            printf("Socket %d has entered Ctrl+C.\n", i);
                            //Remove that socket
                            exitClient(i,&readfds,&numClients,arrayClients);
                        }
                    }
                }
            }
        }
    }

	close(sd);
	return 0;
}

void exitClient(int socket, fd_set * readfds, int * numClients, int arrayClients[]){
    char buffer[250];
    int j; 
    close(socket);
    FD_CLR(socket,readfds);

    //Re-structure the array of clients
    for(j=0; j<(*numClients)-1; j++)
        if(arrayClients[j]==socket)
            break;
    for(; j<(*numClients)-1; j++)
        (arrayClients[j]=arrayClients[j+1]);    
    (*numClients)--;   
    bzero(buffer,sizeof(buffer));
    sprintf(buffer,"Client disconnection: %d\n",socket);    
    for(j=0; j<(*numClients); j++)
        if(arrayClients[j] !=socket)
            send(arrayClients[j],buffer,sizeof(buffer),0);
}

void signalHandler(int signum){
    printf("\nCtrl+C signal received\n");
    signal(SIGINT,signalHandler);    
    //Implement actions to take when the Ctrl+C exception occurs in the server
}
