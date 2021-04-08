#ifndef __BOYER__MOORE_H
#define __BOYER__MOORE_H

#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>




/**
 * Creates the bad symbol table based on the pattern
 */
int* BadSymbolTable( char* pattern);

/**
 * Creates the good suffix table based on the pattern
 */
int* GoodSuffixTable (char* pattern);

//returns the number of matches of pattern in text
void BoyerMoore(char* text, char* pattern);

void BoyerMooreDriver( char* fileName );

#endif

