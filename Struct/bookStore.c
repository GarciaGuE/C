#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book{
	char title[100];
	char author[50];
	float price;
	int units;
};

void clearLine(char *Book){
	if(Book[strlen(Book)-1]=='\n')	Book[strlen(Book)-1]='\0';
}

void checkBook(char *fileName, char *Book){
	FILE *f;
	int found=0;
	char Bookaux[150];
	
	if((f=fopen(fileName, "r"))==NULL){
		printf("\nError opening the file <%s>", fileName);
		exit(-1);
	}
	
	while(fgets(Bookaux, 50, f)!=NULL && !found){
		clearLine(Bookaux);
		if(strcmp(Book, Bookaux)==0){
			found=1;
			printf("The book is in stockBook.\n");
			break;
		}
		fgets(Bookaux, 50, f);
		clearLine(Book);
	}	
	
	fclose(f);
	
	if(found!=1){
		printf("The book is not in stockBook.\n");
	}
}

void addBook(char *fileName){
	struct Book book; 
	FILE *f;
	
	if((f=fopen(fileName, "a"))==NULL){
		printf("\nError opening the file <%s>", fileName);
		exit(-1);
	}
	
	printf("\nEnter the book title: ");
	fgets(book.title, 100, stdin);
	clearLine(book.title);
	fprintf(f, "%s\n", book.title);
	
	printf("\nEnter the author of the book: ");
	fgets(book.author, 50, stdin);
	clearLine(book.author);
	fprintf(f, "%s\n", book.author);
	
	printf("\nEnter the price of the book: ");
	scanf("%f", &book.price);
	fprintf(f, "%f\n", book.price);
	
	printf("\nEnter the number of units available for the book: ");
	scanf("%i", &book.units);
	fprintf(f, "%i\n", book.units);
	
	fclose(f);
}

int countBooks(char *fileName){
	FILE *f;
	int records=0;
	char line[50];

	f=fopen(fileName, "r");
	while(fgets(line, 50, f)!=NULL){
		records++;
		clearLine(line);
	}

	fclose(f);
	
	return (records/4);
}

struct Book *allocateMemory(int numEle){
  	struct Book *bv;
  	if((bv=(struct Book*)malloc(numEle*sizeof(struct Book)))==NULL){
		printf("Error: Memory allocation failed.\n");
		exit(-1);
  	}
  	return bv;
}

struct Book *stockBook(char *fileName){
	FILE *f;
	struct Book *bv;
	if((f=fopen(fileName, "r"))==NULL){
		printf("\nError opening the file <%s>", fileName);
		exit(-1);
	}
	
	char line[50];
	int nEle=countBooks(fileName);
	bv=(allocateMemory(nEle));
	
	for(int i=0; i<nEle; i++){
		fgets(bv[i].title, 50, f);
		clearLine(line);
		fgets(bv[i].author, 50, f);
		clearLine(line);
		fscanf(f, "%f", &bv[i].price);	
		fgetc(f);
		fscanf(f, "%i", &bv[i].units);
		fgetc(f);
		printf("Title: %s", bv[i].title);
		printf("Author: %s", bv[i].author);
		printf("Price: %f\n", bv[i].price);
		printf("Units: %i\n\n", bv[i].units);
	}

	return bv;
}

int fileExists(char *fileName){
	FILE *f;
	f=fopen(fileName, "r");
	
	if(f==NULL)	return 0;
	else{
		fclose(f);
		return 1;
	}
}

int main(int argc, char *argv[]){
	char fileName[500];
	char search[50];
	
	strcpy(fileName, argv[1]);
	if(fileExists(fileName)==0){
		FILE *f;
		f=fopen(fileName, "w");
		fclose(f); 
	}
	
	int *bv;
	int opt=0;
	
	while(opt!=7){
		printf("Select an option: \n");
		printf("	1.Check the existence of a book. \n");
		printf("	2.Add a new book. \n");
		printf("	3.Count the number of different books in stockBook. \n");
		printf("	4.List books in stockBook. \n");
		printf("	5.Sell 'n' units of a book by searching for its title. \n");
		printf("	6.Delete records with 0 units. \n");
		printf("	7.Exit \n");
		
		scanf("%i", &opt);
		switch(opt){
			case(1):
				printf("Enter the book you're looking for: ");
				getchar();
				fgets(search, 50, stdin);
				clearLine(search);
				checkBook(fileName, search);
			break;

			case(2):
				getchar();
				addBook(fileName);
			break;

			case(3):
				getchar();
				printf("Number of different books: %i \n", countBooks(fileName));
			break;

			case(4):
				getchar();
				stockBook(fileName);
			break;

			//Implement case 5 and 6.
			
			case(7):
				printf("Exiting...\n");
			break;

			default:
				printf("No such option exists.\n");
		}
	}

	return 0;
}
