#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include "common.h"

//Function prototype
FILE *fLog=NULL;
void logFunction(char *message){
	int result;
	char fileName[100];
	char messageToWrite[300];
	time_t t;

	//Open the file
	sprintf(fileName,"serverLogs.txt");
	if(fLog==NULL){
		fLog=fopen(fileName,"at");	
		if(fLog==NULL){	
			perror("Error opening the log file");	
			exit(1);
		}
	}

	//Get the current time
	t=time(NULL);
	struct tm *p=localtime(&t);
	strftime(messageToWrite, 1000, "[%Y-%m-%d, %H:%M:%S]", p);

	//Include the timestamp and the message
	sprintf(messageToWrite, "%s --> %s\n", messageToWrite, message);

	// Write to the file
	result=fputs(messageToWrite,fLog);
	if(result<0){
		perror("Error writing to the log file");
	}
	fclose(fLog);
	fLog=NULL;
}

int main(int argc, char **argv){
	//Server-client queue
	mqd_t server, client;

	//Queue attributes
	struct mq_attr attribute;

	//Message exchange
	char buffer[MAX_SIZE];
	char message[MAX_SIZE];

	//Buffer size
	int sizebuffer;

	//Flag for stopping with exit
	int must_stop=0;

	// Initialize queue attributes
    attribute.mq_maxmsg=10;  // Maximum number of messages
    attribute.mq_msgsize=MAX_SIZE;  // Maximum message size
	
	//Queue names
    char serverQueue[MAX_SIZE], clientQueue[MAX_SIZE];
	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    printf ("[Server]: The server queue name is: %s\n", serverQueue);
    sprintf(message, "[Server]: The server queue name is: %s\n", serverQueue );
    logFunction(message);

    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Server]: The client queue name is: %s\n", clientQueue);
    sprintf(message, "[Server]: The client queue name is: %s\n", clientQueue);
    logFunction(message);

    //Opening the queues
	server=mq_open(serverQueue, O_CREAT | O_RDONLY, 0644, &attribute);
    client=mq_open(clientQueue, O_CREAT | O_WRONLY, 0644, &attribute);

    //Error handling for opening
	if(server==(mqd_t)-1 || client==(mqd_t)-1 ){	
   		perror("Error opening the server queue");
        logFunction("Error opening the server queue");
        exit(-1);
	}

	//Queue descriptors and message sending
    printf("[Server]: The server queue descriptor is: %d\n", (int) server);
    sprintf(message, "[Server]: The server queue descriptor is: %d\n", (int) server );
    
	printf("[Server]: The client queue descriptor is: %d\n", (int) client);
    sprintf(message, "[Server]: The client queue descriptor is: %d\n", (int) client );
    logFunction(message);
    
	//Receiving messages
	while(!must_stop){
		//Number of bytes read
		ssize_t bytes;

		//Receive the message
		bytes=mq_receive(server, buffer, MAX_SIZE, NULL );

		//Check for reception errors
		if(bytes<0){
			perror("Error receiving the message");
            logFunction("Error receiving the message");
            exit(-1);
		}

		//Handling SIGINT, SIGTERM and exit
		if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0){
			must_stop=1;
		}
		else if(strncmp(buffer, "SIGINT", strlen("SIGINT"))==0){
			must_stop=1;
		}
		else if(strncmp(buffer, "SIGTERM", strlen("SIGTERM"))==0){
			must_stop=1;
		}
		
		//Client messages
		else{
			printf("Received a message from the client: %s", buffer);
            sprintf(message, "Received a message from the client: %s\n", buffer);
            logFunction(message);
			sizebuffer=strlen(buffer);
			for(int i=0; i<sizebuffer; i++){
				if(buffer[i]==' ' || buffer[i]=='\n' ){
					sizebuffer--;
				}
			}
			sprintf(message, "%d", sizebuffer);

			//Error handling
			if((mq_send(client, message, MAX_SIZE, 0))!=0){
				perror("Error sending the message");
                logFunction("Error sending the message");
                exit(-1);
			}
		}
	} 
	//Error handling for closing
	if((mq_close(server)==(mqd_t)-1) || ((mq_close(client))==(mqd_t)-1)){
		perror("Error closing the server queue");
        logFunction("Error closing the server queue");
        exit(-1);
	}
	
	//Error handling for removal
	if((mq_unlink(serverQueue)==(mqd_t)-1) || ((mq_unlink(clientQueue))==(mqd_t)-1)){
		perror("Error removing the server queue");
        logFunction("Error removing the server queue");
        exit(-1);
	}
	return 0;
}
