/*
* FILE:				outputFile.h
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 25, 2025
* DESCRIPTION:
*
* This is the header file for outputFile.c
*/
#ifndef OUTPUTFILE_H
#define OUTPUTFILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable: 4996) // required by Visual Studio for fopen().

// Constants
#define LOCATION 2048
#define ERROR 1
#define S_RECORD 2
// Prototypes
int outputFileRead(char* inputFileName, char* outputFileName, FILE** outputFile, int format);
#endif //OUTPUTFILE_H