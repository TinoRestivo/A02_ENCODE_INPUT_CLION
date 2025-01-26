/*
* FILE:				asmFile.h
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 25, 2025
* DESCRIPTION:
*
* This is the header file for asmFile.c
*/
#ifndef ASMFILE_H
#define ASMFILE_H
#define ERROR 1
#define MAX_BYTES_PER_LINE  16

int asmFile(FILE* inputFile, FILE* outputFile);
#endif //ASMFILE_H