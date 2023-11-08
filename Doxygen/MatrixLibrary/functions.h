/**
@file functions.h
@brief We have the following functions:
	allocateMatrix->Function responsible for reserving memory for an array of nrows and ncolumns.
	fillMatrix->Function to enter the integers we want
	printMatrix->Function to print the elements of the matrix on the screen
	countDivisibles->Function that, through parameters passed by reference, returns the number of elements divisible by 3 in the matrix and the sum of the latter.
	freeMatrix->Free the memory reserve of the matrix.
*/
#ifndef _LIBRARY_
#define _LIBRARY_
#include <stdio.h>
#include <stdlib.h>
/**
@fn int** allocateMatrix(int rows, int columns);
@param rows=number of rows of the parameters
@param columns=number of rows of the parameters
@param Matrix= Matrix that we are going to write
@author Emilio Garcia Gutierrez
@date 04/13/2020
@version 1.0
*/
int **allocateMatrix(int rows, int columns);
void fillMatrix(int **matrix, int rows, int columns);
void printMatrix(int **matrix, int rows, int columns);
void countDivisibles(int **matrix, int rows, int columns, int *d, int *sum);
void freeMatrix(int ***matrix, int rows);

#endif
