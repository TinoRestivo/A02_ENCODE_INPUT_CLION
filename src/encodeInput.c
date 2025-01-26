/*
* FILE:				encodeInput.c
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 25, 2025
* DESCRIPTION:
*
* This file includes the main function.
* This program generates a assembly file or S19 file from user input or stdin
*/

#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable: 4996) // required by Visual Studio for fopen().

#include "../inc/inputFile.h"
#include "../inc/outputFile.h"
#include "../inc/asmFile.h"
#include "../inc/parseCommandLine.h"
#include "../inc/srec.h"

int main(int argc, char* argv[])
{
	// Initializing input file name
	char inputFileName[FILE_NAME] = { 0 };

	// Initializing ouput file name
	char outputFileName[FILE_NAME] = { 0 };

	// Initializing format specifier
	int outputFormat = 0; // by default 0 - Assembly file output

	int status = parseSwitches(argc, argv, inputFileName, outputFileName, &outputFormat);

	if (status == ERROR)
	{
		return ERROR; // exit program
	}

	// Initiating file streams
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;

	// Working on input file/input
	int ifstatus = inputFileRead(inputFileName, &inputFile);
	if (ifstatus == ERROR)
	{
		return ERROR;
	}

	// Working on output file/input
	int ofstatus = outputFileRead(inputFileName, outputFileName, &outputFile, outputFormat);
	if (ofstatus == ERROR)
	{
		return ERROR;
	}

	if (outputFormat != S_RECORD)
	{
		int success = asmFile(inputFile, outputFile);
		if (success == ERROR)
		{
			//Closing the files in case of failed read/write tasks.
			if (inputFile != stdin)
			{
				//Closing the input file
				if (fclose(inputFile) != 0 && inputFile != NULL)
				{
					printf("ERROR: fclose() for '%s' file failed.\n", inputFileName);
				}
			}

			if (outputFile != stdout) {
				//Closing the input file
				if (fclose(outputFile) != 0 && outputFile != NULL)
				{
					printf("ERROR: fclose() for '%s' file failed.\n", inputFileName);
				}
			}
			return ERROR;
		}
	}
	else
	{
		int success = srecFile(inputFile, outputFile);
		if (success == ERROR)
		{
			//Closing the files in case of failed read/write tasks.
			if (inputFile != stdin)
			{
				//Closing the input file
				if (fclose(inputFile) != 0 && inputFile != NULL)
				{
					printf("ERROR: fclose() for '%s' file failed.\n", inputFileName);
				}
			}

			if (outputFile != stdout) {
				//Closing the input file
				if (fclose(outputFile) != 0 && outputFile != NULL)
				{
					printf("ERROR: fclose() for '%s' file failed.\n", inputFileName);
				}
			}
			return ERROR;
		}
	}

	// Close the input file if it was opened (not stdin)
	if (inputFile != stdin)
	{
		//Closing the input file
		if (fclose(inputFile) != 0 && inputFile != NULL)
		{
			printf("ERROR: fclose() for '%s' file failed.\n", inputFileName);
			return ERROR;
		}
	}

	// Close the output file if it was opened (not stdout)
	if (outputFile != stdout) {
		//Closing the input file
		if (fclose(outputFile) != 0 && outputFile != NULL)
		{
			printf("ERROR: fclose() for '%s' file failed.\n", inputFileName);
			return ERROR;
		}
	}

	return 0;
}