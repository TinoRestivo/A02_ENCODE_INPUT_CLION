/*
* FILE:				srec.h
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 25, 2025
* DESCRIPTION:
*
* This is the header file for srec.c
*/
#ifndef SREC_H
#define SREC_H
#include <stdio.h>
#define S0 "S0"
#define S1 "S1"
#define S5 "S5"
#define S9 "S9"
#define MASK_HIGH_BYTE 0x00FF

#define T_FIELD 2						//portion for s command (s0,s1,s5,s9) size is 2
#define C_FIELD 2						//portion holding byte size is 2
#define A_FIELD 4						//portion holding location is 4
#define DATA_SIZE 2						//each part of data is 2 characters
#define MAX_DATA 16						//each s command can have up to 16 data values
#define M_FIELD 2						//check sum size is 2 characters
#define MAX_LINE_SIZE S_COMMAND_SIZE + BYTE_LENGTH_SIZE + LOCATION_SIZE + DATA_SIZE * MAX_DATA + CHECK_SUM_SIZE
#define OUR_NAMES "TINO-OLGA"
#define OUR_NAMES_LENGTH 9

#define ERROR 1
#define MAX_BYTES_PER_LINE  16

typedef struct SLine
{
	unsigned char* tfield;
	unsigned char* cfield;
	unsigned char* afield;
	unsigned char* dfield;
	int dataLength;
	unsigned char* mfield;
}SLine;

typedef struct Hex2Bytes
{
	unsigned char values[DATA_SIZE + 1];//add 1 for null terminator so sprintf can be used
}Hex2Bytes;

typedef struct Hex4Bytes
{
	unsigned char values[A_FIELD + 1];//add 1 for null terminator so sprintf can be used
}Hex4Bytes;

typedef struct Location
{
	int locationValue;
	Hex4Bytes hex;
}Location;

int srecFile(FILE* inputFile, FILE* outputFile);
void srecAddS0Record(FILE* outputFile);
void srecAddS1Record(Location location, unsigned char* data, int size, FILE* outputFile);
void srecAddS5Record(int numOfS1Lines, FILE* outputFile);
void srecAddS9Record(FILE* outputFile);
void writeSLine(SLine s, FILE* outputFile);
Hex2Bytes createCheckSum(unsigned char count, unsigned short int address, unsigned char* data, int dataSize);
unsigned short int getDataSum(unsigned char* data, int dataSize);
Hex2Bytes charHex2(unsigned char c);
Hex4Bytes intHex4(unsigned short int i);
#endif //SREC_H
