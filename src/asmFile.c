/*
* FILE:			asmFile.c
* PROJECT:		SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 23, 2025
* DESCRIPTION:
*
* This file includes logic for creating the asm file
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/asmFile.h"

/*
	Function: int asmFile(FILE* inputFile, FILE* outputFile)

	Parameters:		FILE* inputFile:		The input file pointer
					FILE* outputFile:	    The output file pointer

	Return Value: int (result Success or Error)

	Description: This function creates the asm file using the input and output file.

*/

int asmFile(FILE* inputFile, FILE* outputFile)
{
	char readLine[256 + 1];//plus 1 for null terminator
	unsigned char outChar;

	while (fgets(readLine, sizeof(readLine), inputFile) != NULL)
	{
		size_t lineLength = strlen(readLine);

		for (int i = 0; i < lineLength; i += MAX_BYTES_PER_LINE) {
			int numOfCharWritten = 0;
			// Loop to write up to 16 bytes in hexadecimal format on one line
			for (int j = i; j < i + MAX_BYTES_PER_LINE && j < lineLength; j++) {
				outChar = (unsigned char)readLine[j];

				// Skipping non-printable characters (like EOF marker or control characters)
				if (outChar < 32 || outChar == 127) {
					continue;
				}
				if (numOfCharWritten == 0)
				{
					fprintf(outputFile, "dc.b\t");
				}
				else
				{
					fprintf(outputFile, ", ");
				}
				fprintf(outputFile, "$%02X", outChar);
				numOfCharWritten++;
			}
			if (numOfCharWritten > 0)
			{
				// End the current line with a newline character
				fprintf(outputFile, "\n");
			}
		}
	}
	// Check if we ended due to EOF or an error
	if (feof(inputFile)) {
		return 0;
	}
	else if (ferror(inputFile))
	{
		printf("ERROR: reading input file.\n");
		return ERROR;
	}

	return 0;
}