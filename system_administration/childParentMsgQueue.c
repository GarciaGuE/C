#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <mqueue.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define MAX_SIZE 1024
#define MSG_STOP "exit"
#define QUEUE_NAME  "/message_queue"

int main(){
	//Message queue
	mqd_t mq;

	//Queue attributes
	struct mq_attr attribute;

	//Message exchange
	char buffer[MAX_SIZE];
	char message[MAX_SIZE];

	//Queue name
    char queue_name[MAX_SIZE];

    //Buffer size
	int sizebuffer;

	//Flag for stopping with "exit"
	int must_stop=0;

	//Number of bytes read
	ssize_t bytes;

	//PID for forking
	pid_t pid;
	int flag;
	int status;

	//Initialize queue attributes
    attribute.mq_maxmsg=10;  //Maximum number of messages
    attribute.mq_msgsize=MAX_SIZE;  //Maximum message size

	//Queue name
    sprintf(queue_name, "%s-%s", QUEUE_NAME, getenv("USER"));

    //Create a child process
	pid=fork();
	switch(pid){
		//Error
		case -1:
			printf("Failed to create the child process\n");
			exit(1);

		//Child process responsible for writing the message and receiving the response from the parent
		case 0: 
			/* Open the queue
            O_CREAT: If it doesn't exist, create it
            O_RDWR: Read/write
            O_RDONLY: Read-only
            O_WRONLY: Write-only
            0644: Permissions rw-r--r--
            Read and write permissions for the owner and read-only for the group and others
            attr: Structure with attributes for the queue */
			mq=mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attribute);
            printf("[CHILD]: The queue name is: %s\n", queue_name);
            printf("[CHILD]: The queue descriptor is: %d\n", (int) mq);

            //Error handling for queue opening
			if(mq==-1){
				perror("[CHILD]: Error opening the queue");
                exit(-1);
			}
			printf("[CHILD]: My PID is %d, and my parent's PID is %d\n", getpid(), getppid());
			printf("[CHILD]: Sending messages to the parent (type \"%s\" to stop):\n", MSG_STOP);
			while(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))){
				printf("> ");
				fgets(buffer, MAX_SIZE, stdin);
				printf("[CHILD]: Generated message: %s", buffer);
				printf("[CHILD]: Sending the message...\n");

				//Send the message and error handling for sending
				if(mq_send(mq, buffer, MAX_SIZE, 0)==-1){
					perror("[CHILD]: Error sending the message");
                    exit(-1);
				}
				printf("[CHILD]: Message sent successfully\n");

				//Receive the message from the parent along with its length
				if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))!=0){
					sizebuffer=mq_receive(mq, message, MAX_SIZE, NULL);
					if(sizebuffer<0){
						perror("Error receiving the message");
                        exit(-1);
                    }
                    printf("[CHILD]: Received the message from the parent: %s\n", message);
				}
			}
			if(mq_close(mq)==-1){
				perror("[CHILD]: Error closing the queue");
				exit(-1);
			}
            printf("[CHILD]: The queue has been closed\n");
		break;

		//Parent process responsible for reading and sending the message length to the child
		default: 
			//Open the queue
			mq=mq_open(queue_name, O_CREAT | O_RDWR, 0644, &attribute);
            printf("[PARENT]: The queue name is: %s\n", queue_name);
            printf("[PARENT]: The queue descriptor is: %d\n", (int) mq);

            //Error handling for queue opening
			if(mq==-1){
				perror("[PARENT]: Error opening the queue");
                exit(-1);
			}

			printf("[PARENT]: My PID is %d and my child's PID is %d\n", getpid(), pid);
			printf("[PARENT]: Receiving messages (blocking)...\n");

			//Recibo de messages
			while(!must_stop){
					bytes=mq_receive(mq, buffer, MAX_SIZE, NULL);
					if(bytes<0){
						perror("[PARENT]: Error receiving the message");
                    	exit(-1);
					} 
					if(strncmp(buffer, MSG_STOP, strlen(MSG_STOP))==0){
						must_stop=1;	
					} 
					else{
						printf("[PARENT]: Received message: %s", buffer);
						sizebuffer=strlen(buffer);
						for(int i=0; i<sizebuffer; i++){
							if(buffer[i]==' ' || buffer[i]=='\n'){
								sizebuffer--;	
							} 
						}
						printf("[PARENT]: Number of received characters->%d\n", sizebuffer);
						sprintf(message, "characters received: %d", sizebuffer);
						if((mq_send(mq, message, MAX_SIZE, 0 ))!=0){
							perror("Error sending the message");
                        	exit(-1);
						} 
					} 
			}
			//Error handling for closing the queue
			if(mq_close(mq)==-1){
				perror("[PARENT]: Error closing the queue");
                exit(-1);
			}

			printf("[PARENT]: The queue has been closed\n");

			//Error handling for queue deletion
			if(mq_unlink(queue_name)==-1){
				perror("[PARENT]: Error deleting the queue");
				exit(-1);
			}

			//Espera del padre a los hijos
	    	while((flag=wait(&status))>0){
		    	if (WIFEXITED(status)) {
			    	printf("Parent Process, Child with PID %ld has finished, status=%d\n", (long int)flag, WEXITSTATUS(status));
		    	}
		    	else if(WIFSIGNALED(status)){
			    	printf("Parent Process, Child with PID %ld has finished due to receiving signal %d\n", (long int)flag, WTERMSIG(status));
		    	}
	    	}
	    	if(flag==(pid_t)-1 && errno==ECHILD){
		    	printf("Parent Process %d, no more children to wait for. errno value=%d, defined as: %s\n", getpid(), errno, strerror(errno));
	    	}
	    	else{
		    	printf("Error en la invocacion de wait o waitpid. Valor de errno=%d, definido como: %s\n", errno, strerror(errno));
		    	exit(EXIT_FAILURE);
	    	} 
	}
	exit(0);
}
