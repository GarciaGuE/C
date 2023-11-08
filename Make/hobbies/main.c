/*! 
    \file main.c
    \brief Main program that allows solving an alphabet soup
    \note Practice
*/

#include <stdio.h>
#include "files.h"
#include "memory.h"
#include "crossword.h"

/*!
 \fn int main()
 \brief Main program
 */
int main(){

  /* Check if the file exists */
  fileExists();

  /* Load the binary file */
  loadBinaryFile();

  /* Allocate memory for the crossword puzzle */
  allocateCrosswordMemory();

  /* Create the crossword puzzle */
  createCrossword();

  /* Print the crossword puzzle */
  printCrossword(); 

  /* Free the allocated memory */
  freeCrosswordMemory();
      
  return 0;
}   

