#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#include "helpers.h"

char* readFile(char* fileName)
{
    if(fileName == NULL)return NULL;

    FILE* fp = fopen(fileName, "r");
    if(fp == NULL)return NULL;
    
    //go to beginning of file
    rewind(fp);

    //seek to the end of the file
    fseek(fp, 0, SEEK_END);

    //get the number of bytes in the file
    unsigned long numBytes = ftell(fp);

    //to hold the content of the file
    char* fileContent = calloc(numBytes+1, sizeof(char));
    //go back to beginning of the file
    rewind(fp);

    //read the file character by character into fileContent
    for(int i=0; i< numBytes; i++)
    {
        fileContent[i] = fgetc(fp);
    }

    fclose(fp);

    return fileContent;
}

char* getInput( void )
{
    char* input = calloc(256, sizeof(char));
    printf("Enter a word to search for\n");
    fgets(input, 256, stdin);
    int len = strlen(input);
    //remove '\n' character
    input[len-1] = '\0';
    return input;
}


char* splice(char* s, int i, int j)
{
    char* substring = calloc((j-i)+1, sizeof(char));
    for(int k = i; k < j; k++)
    {
        substring[k-i] = s[k]; 
    }
    return substring;
}


int getRightMostIndexOfSuffix(char* suffix, char* pattern, int k)
{
    //m = length of pattern
    int m = strlen(pattern);
    //idx of rightmost occurrence
    int idx = -1;
    //set temp = pattern
    //continue until temp >= pattern + (m-k) 
    for(char* temp = pattern; temp < pattern + (m-k); temp++)
    {
        //if temp contains suffix then
        if(strncmp(temp, suffix, k)==0)
        {
            idx = temp-pattern;
        }//end if
    }
    return idx;
}

int shift(int* BadSymbolTable, int* GoodSuffixTable, char c, int k)
{
    int d1 = -1;
   
    int d2 = -1;
   

    //calculate the shfit for d1 using BS table
    if(isupper(c))
    {
        d1 = BadSymbolTable[c-65];
    }
    else if(islower(c))
    {
        d1 = BadSymbolTable[(c - 97)+26];
    }
    else 
    {
        d1 = BadSymbolTable[52];
    }//end if

    //get the distance for d2 using good suffix table
     //if there was no suffix match, then d2 is the shift of the entire pattern length
    if(k == 0)return d1;
    //set d2 to GoodSuffixTable[k-1]
    else d2 = GoodSuffixTable[k-1];
    return d1 > d2 ? d1 : d2;

}
