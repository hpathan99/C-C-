/*********************************************************************************
* Hassan Pathan, hpathan
* 2021 Spring CSE 101 pa1
* Lex.c
* Main function for List ADT
*********************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

#define MAX_LEN 250
typedef char *string;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    FILE *in, *in1, *out;
    int count = 0;
    int i, j, cp;
    int lines = 0;
    char line[MAX_LEN];
    char tokenBuffer[MAX_LEN];

    /*checking for correct number of args*/

    /*open files for reading and writing*/
    in1 = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in1 == NULL)
    {
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    if (out == NULL)
    {
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    /*count number of input lines*/
    while (fgets(tokenBuffer, MAX_LEN, in1) != NULL)
    {
        lines++;
        //printf("%s\n", tokenBuffer);
    }
    string lineArray[lines];

    /*closes file buffer and reopens it*/
    fclose(in1);
    in = fopen(argv[1], "r");
    if (in1 == NULL)
    {
        printf("Unable to open file for reading.\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    /*fills the string array with lines from input file*/
    while (fgets(line, MAX_LEN, in) != NULL)
    {
        i = strlen(line) + 1;
        lineArray[count] = malloc(sizeof(char) * i);
        strcpy(lineArray[count], line);
        count++;
    }

    /*goes through array of the lines inserted above in lex order*/
    List lineofList = newList();
    append(lineofList, 0);

    /*loop to go through array*/
    for (j = 1; j < lines; j++)
    {
        set(lineofList, 0);
        for (i = 0; i < length(lineofList); i++)
        {
            /*gets the appropriate place in list*/
            set(lineofList, i);
            string tmp = lineArray[get(lineofList)];
            cp = strcmp(lineArray[j], tmp);

            if (cp < 0)
            {
                insertBefore(lineofList, j);
                break;
            }
            /*if reached the end of list append*/
            else if (i == length(lineofList) - 1)
            {
                append(lineofList, j);
                break;
            }
        }
    }

    /*prints from the list*/
    for (set(lineofList, 0); index(lineofList) != -1; moveNext(lineofList))
    {
        fprintf(out, "%s", lineArray[get(lineofList)]);
    }

    /*frees the memory space for array*/
    for (j = 0; j < lines; j++)
    {
        free(lineArray[j]);
    }
    freeList(&lineofList);

    /*close files*/
    fclose(in);
    fclose(out);

    return (0);
}
