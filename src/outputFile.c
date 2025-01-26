/*
* FILE:				inputFile.c
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 23, 2025
* DESCRIPTION:
*
* This file includes logic for getting a pointer to the output file
* specified in command line.
*/

#include "../inc/outputFile.h"

/*
	Function: int outputFileRead(char* inputFileName, char* outputFileName, FILE** outputFile, int format)

	Parameters:		char* inputFileName:	Pointer to the input file name if matches the input file name use std out
					char* outputFileName:	Pointer to the output file name
					FILE** outputFile:		Pointer to a pointer of the outputFile
					int format:				Indicates if S_REC or asm file used to determine extension
	Return Value: int (result Success or Error)

	Description: This function gets a pointer to the output file.

*/
int outputFileRead(char* inputFileName, char* outputFileName, FILE** outputFile, int format)
{
	// Initiating output file location
	char outputFileLocation[LOCATION] = "";
	strcpy(outputFileLocation, "./");

	if (strcmp(inputFileName, "") == 0 && strcmp(outputFileName, "") == 0)
	{
		*outputFile = stdout;
	}
	else
	{
		// If output file name is present
		if (strcmp(outputFileName,"\0")!=0)
		{
			strcat(outputFileLocation, outputFileName);
		}
		else if (strcmp(inputFileName, "\0") != 0  && strcmp(outputFileName,"\0")==0)
		{
			if (format == S_RECORD)
			{
				strcpy(outputFileName, inputFileName);
				strcat(outputFileName, ".srec");
			}
			else
			{
				strcpy(outputFileName, inputFileName);
				strcat(outputFileName, ".asm");
			}
			strcat(outputFileLocation, outputFileName);
		}

		//Open output file
		*outputFile = fopen(outputFileLocation, "w");
		if (*outputFile == NULL)
		{
			printf("ERROR: Can't open '%s' file\n", outputFileName);
			return ERROR;
		}
	}

	return 0;
}