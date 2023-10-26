#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <locale.h>

char* getTime(char* format, int dataLength);

int main(){
    int serverSocket;
    struct sockaddr_in Server;
    struct sockaddr_in Client;
    socklen_t clientLength;
    int dataLength=80;
    char data[dataLength];

    // Open server socket
    serverSocket=socket(AF_INET, SOCK_DGRAM, 0);
    if(serverSocket==-1){
        fprintf(stderr, "Cannot open server socket\n");
        exit (-1);
    }
    Server.sin_family=AF_INET;
    Server.sin_port=htons(3160); // Used port is 3160
    Server.sin_addr.s_addr=htonl(INADDR_ANY); // Used address is any of the system
    int bindResult=bind(serverSocket, (struct sockaddr *)&Server, sizeof(Server));
    if(bindResult==-1){
        fprintf(stderr, "Bind Error: Cannot assign the address specified to the socket referred\n");
        close (serverSocket);
        exit (-1);
    }
    clientLength=sizeof(Client);
    while(1){
        fprintf(stderr, "\nServer waiting requests!\n");
        int received=recvfrom(
            serverSocket,
            data,
            dataLength,
            0,
            (struct sockaddr *) &Client,
            &clientLength
        );
        if(received){
            printf("Request received: %s\n", data);
            char* response=getTime(data, dataLength);
            printf("Sending response: %s\n", response);
            int sended=sendto(
                serverSocket,
                response,
                dataLength,
                0,
                (struct sockaddr *) &Client,
                clientLength);
            free(response);
            if(sended==-1) fprintf(stderr, "Error sending response\n");
            else printf("Response sent successfully!\n");
        }
    }
    close(serverSocket);
    return 0;
}

char * getTime(char * format, int dataLength){
    time_t seconds;
    struct tm* localTime;
    char* string=(char *)calloc(1, dataLength);

    // Seconds from 01/01/1975 to today
    time(&seconds);

    // If replace "es_ES" for NULL or empty string, get value from env vars of our system
    setlocale(LC_ALL,"es_ES");

    // Returns localTime pointer for a given timestamp
    localTime=localtime(&seconds);

    //strcmp compares two strings and return 0 if both strings are indetical
    //strftime returns time in the specified format
    if(!strcmp(format, "DAY"))
        strftime(string,80,"%A, %d de %B de %Y", localTime);
    else if(!strcmp(format, "TIME"))
        strftime(string,80,"%H:%M:%S", localTime);
    else if(!strcmp(format, "DAYTIME")) 
        strftime(string,80,"%A, %d de %B de %Y; %H:%M:%S", localTime);
    return string; 
}