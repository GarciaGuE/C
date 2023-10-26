#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc, char* argv[]){
    int clientSocket;
    int option=0;
    int dataLength=80;
    char data[dataLength];
    struct sockaddr_in Server;
    socklen_t serverLength;
    char* ip=argv[1];
    int retry=atoi(argv[2]);
    int exitCode=0;
    while(option<1 || option>3){
        printf("1. TIME\n");
        printf("2. DAY\n");
        printf("3. DAYTIME\n");
        printf("Enter the request to perform: ");
        scanf("%d", &option);
    }
    switch(option){
        case 1:
            strcpy(data, "TIME");
        break;
        case 2:
            strcpy(data, "DAY");
        break;
        case 3:
            strcpy(data, "DAYTIME");
        break;
    }
    clientSocket=socket(AF_INET, SOCK_DGRAM, 0);
    if (clientSocket==-1){
        printf ("Cannot open client socket\n");
        exit (-1);
    }
    Server.sin_family=AF_INET;
    Server.sin_port=htons(3160);
    Server.sin_addr.s_addr=inet_addr(ip);
    serverLength = sizeof(Server);
    while(retry>0 && exitCode==0){
        int sent=sendto(
            clientSocket,
            (char *) &data,
            dataLength,
            0,
            (struct sockaddr *) &Server, serverLength
        );
        if(sent==-1) fprintf(stderr, "Error sending request");
        else{
            struct timeval timeout;
            fd_set read;
            timeout.tv_sec = 5;
            timeout.tv_usec = 0;
            FD_ZERO(&read);
            FD_SET(clientSocket,&read);
            exitCode=select(clientSocket+1,&read,NULL,NULL,&timeout);
            if(exitCode==-1) printf("An error occurred in select.\n");
            else if(exitCode==0) printf("Timeout waiting response. Retrying: %d attemps remaining\n", --retry);
            else{
                int received=recvfrom(
                    clientSocket,
                    (char *) &data,
                    dataLength,
                    0,
                    (struct sockaddr *) &Server,
                    &serverLength
                );
                if(received>0)
                    printf("Response received: %s\n", data);
                else
                    printf("Error: No response received from server\n");
            }
        }
    }
    close(clientSocket);
    return 0;
}