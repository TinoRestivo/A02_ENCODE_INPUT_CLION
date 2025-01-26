/*
* FILE:				inputFile.c
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 25, 2025
* DESCRIPTION:
*
* This file includes logic for getting a pointer to the input file
* specified in command line.
*/

#include "../inc/inputFile.h"

/*
	Function: int inputFileRead(char* fileName, FILE** inputFile)

	Parameters:		char* fileName:		Pointer to The input file name
					FILE** inputFile:	    Pointer to pointer of input file

	Return Value: int (result Success or Error)

	Description: This function gets a pointer to the input file.

*/
int inputFileRead(char* fileName, FILE** inputFile)
{
	if (strcmp(fileName, "\0") == 0)
	{
		*inputFile = stdin;
	}
	else
	{
		char inputFileLocation[LOCATION] = "";
		strcpy(inputFileLocation, "./");
		strcat(inputFileLocation, fileName);

		*inputFile = fopen(inputFileLocation, "rb");
		if (*inputFile == NULL)
		{
			printf("ERROR: Can't open '%s' file\n", fileName);
			return ERROR;
		}
	}

	return 0;
}