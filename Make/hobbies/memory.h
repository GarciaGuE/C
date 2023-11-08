/*! 
    \file memory.h
    \brief Prototypes of memory-related functions
    \note Practice
*/
#ifndef _MEMORY_H_
#define _MEMORY_H_

/*!
 \fn void allocateAlphabetSoupMemory();
 \brief Allocate memory for an alphabet soup
 */
void allocateAlphabetSoupMemory();

/*!
 \fn  void allocateCrosswordMemory();
 \brief Allocate memory for a crossword puzzle
 */
void allocateCrosswordMemory();

/*!
 \fn  void freeAlphabetSoupMemory();
 \brief Free memory used by the word search puzzle
 */
void freeAlphabetSoupMemory();

/*!
 \fn  void freeCrosswordMemory();
 \brief Free memory used by the crossword puzzle
 */
void freeCrosswordMemory();

#endif
