#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/inputFile.h"
int inputFileRead(char* fileName, FILE** inputFile)
{
	if (strcmp(fileName, "\0") == 0)
	{
		*inputFile = stdin;
	}
	else
	{
		char inputFileLocation[LOCATION] = "";
		strcpy(inputFileLocation, ".\\");
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