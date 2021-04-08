



#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "Boyer-Moore.h"
#include "helpers.h"
#include <time.h>

//pattern must be aplhabetic only
int* BadSymbolTable(char* pattern)
{
    //create a table with 53 ints, one for each letter in upper and lower case and one for every other character
    int* badSymbolTable = calloc(53, sizeof(int));

    int m = strlen(pattern);

    for(int i = 0; i < 53; i++)badSymbolTable[i] = m;

    //initialize the bad symbol table
    for(int i = 0; i < m-1; i++)
    {
        char c = pattern[i];
        //if upper case then go to first half of table
        if(isupper(c))
        {
            int offset = c - 65;
            badSymbolTable[offset] = m - 1 - i;
        }
        //if lower case go to second half of table
        else if(islower(c))
        {
            int offset = (c - 97) + 26;
            badSymbolTable[offset] = m - 1 - i;
        }
    }

    return badSymbolTable;
}

int* GoodSuffixTable(char* pattern)
{
    //length of pattern
    int m = strlen(pattern);

    int* goodSuffixTable = calloc(m, sizeof(int));
    //k is the suffix size
    int k = 1;

    while(k < m)
    {
        //create the suffix
        char* suffix = splice(pattern, (m-k), m);
        //get its rightmost ocurrence to its left in pattern
        int idx = getRightMostIndexOfSuffix(suffix, pattern, k);
        free(suffix);
        //if you found the rightmost ocurrence of the suffix
        if(idx != -1)
        {
            goodSuffixTable[k-1] = (m-k) - idx;
        }
        //if you did not find the rightmost occurrence of the suffix
        else if(idx == -1 && k > 1)
        {
            goodSuffixTable[k-1] = goodSuffixTable[k-2];
        }
        //if you did not find the rightmost occurrence of the suffix and suffix is of size 1
        else 
        {
            goodSuffixTable[k-1] = m;
        }//end if

        //increment suffix size
        k++;
    }//end while

    return goodSuffixTable;
}//end func




/**Boyer moore algorithm***/

void BoyerMoore(char* text, char* pattern)
{
    //keep track of number of shifts and matches
    int shiftCount, numMatches = 0;
    //n = length of text
    int n = strlen(text);
    //m = length of pattern
    int m = strlen(pattern);
    //get BadSymbolTable
    int* t1 = BadSymbolTable(pattern);
    //get GoodSuffixTable
    int* t2 = GoodSuffixTable(pattern);

    //i is index for the text
    int i = m-1;

    //while not at the end of the text
    while(i < n)
    {
     
        //k = number of matched characters
        int k = 0;
        //compare pattern with text going right to left along the pattern until mismatch is found
        while(pattern[m-1-k] == text[i - k] && k < m)
        {
            k++;
        }
        //if k = m then match found
        if(k == m)
        {
            //match found, shift by the entire pattern length
            numMatches++;
            i += m; 
        }else 
        {
            i += shift(t1, t2, text[i], k);
        }//end if

        //increase the number of shifts
        shiftCount++;
    }//end while


    //print the results. 

    printf("Found %d matches of the pattern \"%s\" using %d shifts\n", numMatches, pattern, shiftCount);
    free(t1);
    free(t2);
}//end function


/**
 * 
Runs the program
 */
void BoyerMooreDriver( char* fileName )
{
    //Open the file as text
    char* text = readFile(fileName);
    if(text == NULL)
    {
        printf("Enter a file in the command line\n");
        printf("To run program type './boyermoore <file.txt>'\n");
        exit(1);
    }

    //get the pattern from the user
    char* pattern = getInput();

    //start the time
    clock_t start, end;
    start = clock();
    //call BoyerMoore
    BoyerMoore(text, pattern);
    //end the time
    end = clock();
    //print the running time
    printf("The program completed running in %.6f seconds\n", ((double)(end - start))/CLOCKS_PER_SEC);
    free(text);
    free(pattern);

}