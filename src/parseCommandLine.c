#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/parseCommandLine.h"

int parseSwitches(int argc, char* argv[], char* inputFileName, char* outputFileName, int* outputFormat)
{
	// Checking for arguments count
	if (argc > ARGS_COUNT)
	{
		printHelp();
		return ERROR;
	}

	// Checking for invalid switch
	for (int i = 1; i < argc; i++)
	{
		if (strncmp(argv[i], "-o", 2) != 0 &&  // For -o
			strncmp(argv[i], "-i", 2) != 0 &&  // For -i
			strncmp(argv[i], "-h", 2) != 0 &&  // For -h
			strncmp(argv[i], "-srec", 4) != 0) // For -srec
		{
			printHelp();
			return ERROR;
		}
	}

	// Checking for -h switch
	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-h") == 0)
		{
			printHelp();
			return ERROR;
		}
	}

	// Checking for -srec switch
	for (int i = 1; i < argc; i++)
	{
		if (strncmp(argv[i], "-srec", 4) == 0)
		{
			// Updating output format to 1.
			*outputFormat = S_RECORD;
			break;
		}
	}

	// Checking for -i switch
	for (int i = 1; i < argc; i++)
	{
		if (strncmp(argv[i], "-i", 2) == 0)
		{
			// Updating input file name
			strncpy(inputFileName, argv[i] + 2, strlen(argv[i]) - 2);
			inputFileName[strlen(argv[i]) - 2] = '\0';  // Ensure null termination
			break;
		}
	}

	// Checking for -o switch
	for (int i = 1; i < argc; i++)
	{
		if (strncmp(argv[i], "-o", 2) == 0)
		{
			// Updating output file name
			strncpy(outputFileName, argv[i] + 2, strlen(argv[i]) - 2);
			outputFileName[strlen(argv[i]) - 2] = '\0';  // Ensure null termination
			break;
		}
	}

	return 0;
}

void printHelp(void)
{
	printf("Usage: my_program [options]\n");
	printf("Options:\n");
	printf("  -i<INPUTFILENAME>		Specifies input file.\n");
	printf("  -o<OUTPUTFILENAME>	Specifies output file.\n");
	printf("  -srec					Specifies output format as S-Record format.\n");
	printf("  -h					Shows this help message.\n");
}