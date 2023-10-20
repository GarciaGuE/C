#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <errno.h> 
#include <string.h> 


int main(){
	//PID for forking
	pid_t pid;
	int flag;
	int status;

	//To control the values returned by functions (error control)
	float result; 
	float random;

	//Descriptors for both ends
	int fileDes[2];
	float sum=0;
	
	//Creating a pipe
	result=pipe(fileDes);

	//Error control
	if(result==-1){
		printf("\nERROR creating the pipe.\n");
		exit(1);
	}

	printf("[PARENT]: My PID is %d and I'm going to fork.\n", getppid());
	pid=fork();

	switch (pid){
		case -1:
			printf("Error forking: %s\n", strerror(errno));
            return EXIT_FAILURE;
		case 0:
			printf ("[CHILD]: My PID is %d and my parent's PID is %d\n", getpid(), getppid());
			
			//Child reading
			close(fileDes[1]);

			//Receiving the number
			result=read(fileDes[0], &sum, sizeof(int));

			//Error control for receiving the number
			if(result!=sizeof(int)){
				printf("\n[CHILD]: ERROR reading from the pipe...\n");
				exit(EXIT_FAILURE);
			}

			//Displaying the received number
			printf("[CHILD]: Sum from the pipe: %f\n", sum);		
			printf("[CHILD]: Pipe closed...\n");
			close(fileDes[0]);
			break;

		default:
			printf("[PARENT]: My PID is %d and my child's PID is %d\n", getpid(), pid);
			
			//Writing
			close(fileDes[0]);
			srand48(time(NULL));

			//Creating and summing random numbers
			for(int i=0; i<2; i++){			
				random=drand48()*100; 
				printf("[PARENT]: Generated random number: %f\n", random);
				sum=sum+random;
			}
			printf("[PARENT]: Writing the sum %f to the pipe...\n", sum);

			//Sending the number
			result=write(fileDes[1], &sum, sizeof(float));
			if(result!=sizeof(float)){
				printf("\n[PARENT]: ERROR writing to the pipe...\n");
				exit(EXIT_FAILURE);
			}

			//Closing the write end
			close(fileDes[1]);
			printf("[PARENT]: Pipe closed...\n");

			//Espera del hijo
			while((flag=wait(&status))>0){
				if(WIFEXITED(status)){
					printf("Parent Process, Child with PID %ld finished, status=%d\n", (long int)flag, WEXITSTATUS(status));
				} 
				else if(WIFSIGNALED(status)){
					printf("Parent Process, Child with PID %ld terminated due to receiving signal %d\n", (long int)flag, WTERMSIG(status));
				} 		
			}
			if(flag==(pid_t)-1 && errno==ECHILD){
				printf("Parent Process %d, no more children to wait for. Errno value = %d, defined as: %s\n", getpid(), errno, strerror(errno));
			}
			else{
				printf("Error in the invocation of wait or waitpid. Errno value=%d, defined as: %s\n", errno, strerror(errno));
				exit(EXIT_FAILURE);
			}				 
	}
	exit(EXIT_SUCCESS);
}
