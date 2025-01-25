#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/outputFile.h"
int outputFileRead(char* inputFileName, char* outputFileName, FILE** outputFile, int format)
{
	if (strcmp(inputFileName, "") == 0 && strcmp(outputFileName, "") == 0)
	{
		*outputFile = stdout;
	}
	else
	{
		// If input file name is present
		if (strcmp(inputFileName, "\0") != 0)
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
		}

		char outputFileLocation[LOCATION] = "";
		strcpy(outputFileLocation, ".\\");
		strcat(outputFileLocation, outputFileName);

		//Open output file
		*outputFile = fopen(outputFileLocation, "w+");
		if (*outputFile == NULL)
		{
			printf("ERROR: Can't open '%s' file\n", outputFileName);
			return ERROR;
		}
	}

	return 0;
}