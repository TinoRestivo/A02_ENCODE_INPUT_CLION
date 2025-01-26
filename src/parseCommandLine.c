/*
* FILE:				parseCommandLine.c
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 23, 2025
* DESCRIPTION:
*
* This file includes logic for parsing the command line
*/

#include "../inc/parseCommandLine.h"
/*
	Function: int parseSwitches(int argc, char* argv[], char* inputFileName, char* outputFileName, int* outputFormat)

	Parameters:		int argc:				number of command line arguments
					char* argv[]:			The command line arguments
					char* inputFileName:	The input file name
					char* outputFileName:	The output file name
					int* format:			Indicates if S_REC or asm file is selected from command line
	Return Value: int (result Success or Error)

	Description: This function gets the command line options, user can select a input and a output file and
	if asm file is selected or srec file is selected, if input file not selected stdin is used.If no input file and
	no output file specified stdout will be used

*/
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
/*
	Function: void printHelp(void)

	Parameters:		void
	Return Value:	void

	Description: This function shows the command line options.

*/
void printHelp(void)
{
	printf("USAGE: encodeInput [options]\n");
	printf("[OPTIONS]:\n");
	printf("  -i<INPUTFILENAME>\tSpecifies input file.\n");
	printf("  -o<OUTPUTFILENAME>\tSpecifies output file.\n");
	printf("  -srec\t\t\tSpecifies output format as S-Record format.\n");
	printf("  -h\t\t\tShows this help message.\n");
}