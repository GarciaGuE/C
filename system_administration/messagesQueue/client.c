#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <mqueue.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include "common.h"

//Function prototype
FILE *fLog=NULL;
void logFunction(char *message){
	int result;
	char fileName[100];
	char messageToWrite[300];
	time_t t;

	//Open the file
	sprintf(fileName,"clientLogs.txt");
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

	//Write to the file
	result=fputs(messageToWrite,fLog);
	if(result<0){
		perror("Error writing to the log file");
	}
	fclose(fLog);
	fLog=NULL;
}

//Server queue
mqd_t server;
mqd_t client;
void SigInt(int signal){
	//Save SIGINT
	char buffer[100];
	sprintf(buffer, "[Client]: Received the SIGINT signal with integer code %d\n", signal);
	logFunction(buffer);

	//Send the signal
	if(mq_send(server, "SIGINT", strlen("SIGINT"), 0)!=0){
		perror("Error sending the message");
		exit(-1);
	}

	//Close the queues
	if((mq_close(server)==(mqd_t)-1) || ((mq_close(client))==(mqd_t)-1)){
		perror("Error closing the server queue");
		logFunction("Error closing the server queue");
		exit(-1);
	}

	exit(-1);
}

void SigTerm(int signal){
	//Save SIGTERM
	char buffer[100];
	sprintf(buffer, "[Client]: Received the SIGTERM signal with integer code %d\n", signal);
	logFunction(buffer);

	//Send the signal
	if(mq_send(server, "SIGTERM", strlen("SIGTERM"), 0)!=0){
		perror("Error sending the message");
		exit(-1);
	}

	//Close the queues
	if((mq_close(server)==(mqd_t)-1) || ((mq_close(client))==(mqd_t)-1)){
		perror("Error closing the server queue");
		logFunction("Error closing the server queue");
		exit(-1);
	}
	
	exit(-1);
}

int main(int argc, char **argv){
	//Handle signals
	signal(SIGINT, &SigInt);
	signal(SIGTERM, &SigTerm);

	//Read bytes
	ssize_t bytes_read;

	//Message exchange
	char buffer[MAX_SIZE]; 
	char message[MAX_SIZE];

    //Queue names
    char serverQueue[MAX_SIZE], clientQueue[MAX_SIZE];
	sprintf(serverQueue, "%s-%s", SERVER_QUEUE, getenv("USER"));
    sprintf(message,"[Client]: The server queue name is: %s\n", serverQueue);
    logFunction(message);

    sprintf(clientQueue, "%s-%s", CLIENT_QUEUE, getenv("USER"));
    printf("[Client]: The client queue name is: %s\n", clientQueue);
    sprintf(message, "[Client]: The client queue name is: %s\n", clientQueue);
    logFunction(message);

    //Opening the queues
    server=mq_open(serverQueue, O_WRONLY);
    client=mq_open(clientQueue, O_RDONLY);

    //Error handling for opening
	if(server==(mqd_t)-1 || client==(mqd_t)-1){
      	perror("Error opening the queues");
        logFunction("Error opening the queues");
        exit(-1);
	}

	//Descriptor and message sending
    printf("[Client]: The server queue descriptor is: %d\n", (int) server);
    sprintf(message, "[Client]: The server queue descriptor is: %d\n", (int) server);
    logFunction(message);

    printf("[Client]: The client queue descriptor is: %d\n", (int) client);
    sprintf(message, "[Client]: The client queue descriptor is: %d\n", (int) client);
    logFunction(message);

	printf("Sending messages to the server (type \"%s\" to stop):\n", MSG_STOP);
	sprintf(message, "Sending messages to the server (type \"%s\" to stop):\n", MSG_STOP);
	
	//Keyboard input
	while(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))){	
		printf(">");
		fgets(buffer, MAX_SIZE, stdin);

		//Control message sending
		if(mq_send(server, buffer, MAX_SIZE, 0)!=0){
            perror("Error sending the message");
            logFunction("Error sending the message");
            exit(-1);
		}

		//Receiving messages from the server
		if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))!=0){
			bytes_read=mq_receive(client, message, MAX_SIZE, NULL);
			if(bytes_read<0){
				perror("Error receiving the message");
                logFunction("Error receiving the message");
                exit(-1);
			}
			printf("Number of received characters: %s\n", message);
            logFunction("Number of received characters: ");
            logFunction(message);
		}
	}
	//Error handling for closing the queues
	if(mq_close(server)==(mqd_t)-1 || mq_close(client)==(mqd_t)-1){
		perror("Error closing the server queue");
        logFunction("Error closing the server queue");
        exit(-1);
	}
	
	return 0;
}