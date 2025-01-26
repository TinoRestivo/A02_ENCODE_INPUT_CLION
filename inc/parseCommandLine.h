/*
* FILE:				parseCommandLine.h
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 25, 2025
* DESCRIPTION:
*
* This is the header file for parseCommandLine.c
*/
#ifndef PARSECOMMANDLINE_H
#define PARSECOMMANDLINE_H
#pragma warning(disable: 4996) // required by Visual Studio for fopen().
// Constants
#define ARGS_COUNT 5
#define FILE_NAME 50
#define S_RECORD 2
#define ERROR 1

// Function prototypes
void printHelp(void);
int parseSwitches(int argc, char* argv[], char* inputFileName, char* outputFileName, int* outputFormat);
#endif //PARSECOMMANDLINE_H