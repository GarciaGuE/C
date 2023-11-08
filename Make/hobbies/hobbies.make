# Symbolic target
all: crossword.x clean

# Rule to build the executable
crossword.x: files.o crossword.o main.o libMemory.a
	gcc files.o crossword.o main.o libMemory.a -o crossword.x

# Rule to build the library
libMemory.a: allocateMemory.o freeMemory.o
	ar -rsv libMemory.a allocateMemory.o freeMemory.o

# Rule to build objects
allocateMemory.o: allocateMemory.c memory.h
	gcc -c allocateMemory.c

freeMemory.o: freeMemory.c memory.h
	gcc -c freeMemory.c

main.o: main.c files.h memory.h crossword.h
	gcc -c main.c

files.o: files.c files.h
	gcc -c files.c

crossword.o: crossword.c crossword.h
	gcc -c crossword.c

.PHONY: clean
clean:
	@echo Deleting files.o
	@rm *.o