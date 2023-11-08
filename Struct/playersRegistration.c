#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Program that allows managing basketball players for a city's team. The information of each player will be stored in the following structure:
struct PlayerCard{
	char name[50];
	int number;
	float weight;
	int height;
};

// The program will sequentially perform the following operations:
// a) Create a dynamic array of players.
// b) List the registered players on the team, with their characteristics (number, weight, height).
// c) Delete all players with an 'a' in their name.
// d) List the players again.
// e) Free memory when done.
struct PlayerCard *allocateMemory(int n){
	struct PlayerCard *players;
	players=(struct PlayerCard*)calloc(n,sizeof(struct PlayerCard));
	
	if(players==NULL){
		printf("Error: couldn't reserve memory...\n");
		exit -1;
	}

	return players;
}

void readPlayers(struct PlayerCard *players, int n){
	for(int i=0; i<n; i++){
		printf("PLAYER[%i] DATA\n---------------\n", i+1);
		printf("Enter name: ");
		scanf("%s", players[i].name);
		
		printf("Enter number: ");
        scanf("%i", &players[i].number);

        printf("Enter weight (kg): ");
        scanf("%f", &players[i].weight);
        
		printf("Enter height (cm): ");
        scanf("%i", &players[i].height);
		printf("<---------------------------------------->\n");
	}
}

void printPlayers(struct PlayerCard *players, int n){
	for(int i=0; i<n; i++){
		printf("PLAYER[%i] DATA\n---------------\n", i+1);
		printf("Name: %s\n", players[i].name);
		printf("Number: %i\n", players[i].number);
		printf("Weight: %f kg\n", players[i].weight);
		printf("Height: %i cm\n", players[i].height);
		printf("<---------------------------------------->\n");
	}
}

void freeMemory(struct PlayerCard **players, int n){
	free(*players);
	*players=NULL;
}

void deletePlayers(struct PlayerCard *players, int n){
	int k;
	for(int i=0; i<n; i++){
		for(int m=0; players[i].name[m]!='\0'; m++ ){ 
			if(toupper(players[i].name[m])=='A'){
				k=i;
				while(k<n){
					players[k]=players[k+1];
					k++;
				}
				n--;
			}
		}
	}
	players=(struct PlayerCard*)realloc(players, n*sizeof(struct PlayerCard));
	
	if(players == NULL){
		printf("Error: couldn't allocate new memory...\n");
		exit -1;
	}
	
	printf("The new players are:\n");
	printPlayers(players, n);
	
	freeMemory(&players, n);
}

int main(){
	struct PlayerCard *players;
	int n;
	printf("Enter the number of players: ");
    scanf("%i", &n);

	players=allocateMemory(n);
	
	printf("Memory reserved successfully...\n");
	
	readPlayers(players, n);
	printPlayers(players, n);
	deletePlayers(players, n);
	
	return 0;
}
