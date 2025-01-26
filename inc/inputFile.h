/*
* FILE:				inputFile.h
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 25, 2025
* DESCRIPTION:
*
* This is the header file for inputFile.c
*/

#ifndef INPUTFILE_H
#define INPUTFILE_H
#include <stdio.h>
#pragma warning(disable: 4996) // required by Visual Studio for fopen().

// Constants
#define LOCATION 2048
#define ERROR 1

// Prototypes
int inputFileRead(char* fileName, FILE** inputFile);

int asmFile(FILE* inputFile, FILE* outputFile);
#endif //INPUTFILE_H