#ifndef _HELPERS_H_
#define _HELPERS_H_

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
/**
 * Reads in a file as a char* 
 **/
char* readFile(char* fileName);

/**
 * Gets user input and returns it as a char*
 */
char* getInput( void );

/**
 * Copies a string from index i to j as such - cpy = s[i ...j) . Similar 
 to higher level splice functions
 Returns NULL if i > j or i < 0 or j > strlen(s)
 **/
char* splice(char* s, int i, int j);

/**
 * Gets the rightmost index 
 of suffix in pattern of size k 
 that is to the left of suffix in pattern
 */
int getRightMostIndexOfSuffix(char* suffix, char* pattern, int k);

/**
 * Returns the max of BadSymbolTable[c] and GoodSuffixTable[k]
 */
int shift(int* BadSymbolTable, int* GoodSuffixTable, char c, int k);


#endif