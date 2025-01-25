/*
* FILE:			srec.c
* PROJECT:		SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 23, 2025
* DESCRIPTION:
*
* This file generates a S19 file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/srec.h"

int srecFile(FILE* inputFile, FILE* outputFile)
{
	Location currentLocation = { 0,{'0','0','0','0'} };
	int value;
	int returnStatus = 0;
	int doneRead = 0;
	int dataCountCurrentSRecord = 0;
	int s1Count = 0;
	unsigned char sData[MAX_BYTES_PER_LINE];

	srecAddS0Record(outputFile);//Writes S0 line
	value = fgetc(inputFile);
	while (value != EOF)
	{
		sData[dataCountCurrentSRecord] = (unsigned char)value;
		dataCountCurrentSRecord++;
		if (dataCountCurrentSRecord >= MAX_BYTES_PER_LINE)
		{
			srecAddS1Record(currentLocation, sData, dataCountCurrentSRecord, outputFile);//Writes S1 line
			currentLocation.locationValue += dataCountCurrentSRecord;
			currentLocation.hex = intHex4(currentLocation.locationValue);
			s1Count++;
			dataCountCurrentSRecord = 0;
		}
		value = fgetc(inputFile);
	}

	if (dataCountCurrentSRecord > 0)
	{
		srecAddS1Record(currentLocation, sData, dataCountCurrentSRecord, outputFile);//Writes final S1 line
		currentLocation.locationValue += dataCountCurrentSRecord;
		currentLocation.hex = intHex4(currentLocation.locationValue);
		s1Count++;
		dataCountCurrentSRecord = 0;
	}

	if (feof(inputFile)) {
		returnStatus = 0;
	}
	else if (ferror(inputFile))
	{
		printf("ERROR: reading input file.\n");
		returnStatus = ERROR;
	}

	srecAddS5Record(s1Count, outputFile);//Writes S5 line
	srecAddS9Record(outputFile);//Writes S9 line

	return returnStatus;
}

void srecAddS0Record(FILE* outputFile)
{
	unsigned char calcLength = OUR_NAMES_LENGTH + (A_FIELD + M_FIELD) / 2;

	Hex2Bytes cfield = charHex2(calcLength);

	Location location0 = { 0,{'0','0','0','0'} };

	Hex2Bytes mfield = createCheckSum(calcLength, location0.locationValue, OUR_NAMES, OUR_NAMES_LENGTH);

	SLine s = { S0,cfield.values,location0.hex.values,OUR_NAMES,OUR_NAMES_LENGTH,mfield.values };

	writeSLine(s, outputFile);
}

void srecAddS1Record(Location location, unsigned char* data, int size, FILE* outputFile)
{
	SLine s = { 0 };

	s.tfield = S1;
	s.afield = location.hex.values;
	s.dataLength = size;
	unsigned char calcLength = s.dataLength + (A_FIELD + M_FIELD) / 2;
	Hex2Bytes cfield = charHex2(calcLength);
	s.cfield = cfield.values;
	s.dfield = data;
	Hex2Bytes mfield = createCheckSum(calcLength, location.locationValue, s.dfield, s.dataLength);
	s.mfield = mfield.values;
	writeSLine(s, outputFile);
}

void srecAddS5Record(int numOfS1Lines, FILE* outputFile)
{
	SLine s = { 0 };
	s.tfield = S5;
	Hex4Bytes s1numOfLinesHex = intHex4(numOfS1Lines);
	s.afield = s1numOfLinesHex.values;
	s.dataLength = 0;
	unsigned char calcLength = (A_FIELD + M_FIELD) / 2;
	Hex2Bytes cfield = charHex2(calcLength);
	s.cfield = cfield.values;
	s.dfield = NULL;
	s.dataLength = 0;
	Hex2Bytes mfield = createCheckSum(calcLength, numOfS1Lines, NULL, 0);
	s.mfield = mfield.values;
	writeSLine(s, outputFile);
}

void srecAddS9Record(FILE* outputFile)
{
	SLine s = { 0 };
	Location location0 = { 0,{'0','0','0','0'} };
	s.tfield = S9;
	s.afield = location0.hex.values;
	s.dataLength = 0;
	unsigned char calcLength = (A_FIELD + M_FIELD) / 2;
	Hex2Bytes cfield = charHex2(calcLength);
	s.cfield = cfield.values;
	s.dfield = NULL;
	Hex2Bytes mfield = createCheckSum(calcLength, location0.locationValue, s.dfield, s.dataLength);
	s.mfield = mfield.values;
	writeSLine(s, outputFile);
}

void writeSLine(SLine s, FILE* outputFile)
{
	for (int i = 0; i < T_FIELD; i++)
	{
		fprintf(outputFile, "%c", s.tfield[i]);
	}
	for (int i = 0; i < C_FIELD; i++)
	{
		fprintf(outputFile, "%c", s.cfield[i]);
	}
	for (int i = 0; i < A_FIELD; i++)
	{
		fprintf(outputFile, "%c", s.afield[i]);
	}
	for (int i = 0; i < s.dataLength; i++)
	{
		Hex2Bytes data = charHex2(s.dfield[i]);
		fprintf(outputFile, "%c%c", data.values[0], data.values[1]);
	}
	for (int i = 0; i < M_FIELD; i++)
	{
		fprintf(outputFile, "%c", s.mfield[i]);
	}
	fprintf(outputFile, "\n");
}

Hex2Bytes createCheckSum(unsigned char count, unsigned short int address, unsigned char* data, int dataSize)
{
	unsigned short int dataSum = getDataSum(data, dataSize);
	//step 1
	//add up the count, address, data sum
	unsigned short int sum = count + address + dataSum;

	//step 2
	//take the 1's complement
	unsigned short int onesComplement = ~sum;
	//step 3
	//take the least significant byte

	unsigned char finalValue = onesComplement & MASK_HIGH_BYTE;

	//write it out as a 2 digit hexidecimal
	return charHex2(finalValue);
}

unsigned short int getDataSum(unsigned char* data, int dataSize)
{
	unsigned short int sum = 0;
	for (int i = 0; i < dataSize; i++)
	{
		sum = sum + data[i];
	}
	return sum;
}

Hex2Bytes charHex2(unsigned char c)
{
	Hex2Bytes returnValue = { 0 };
#pragma warning(disable: 4996)
	sprintf(returnValue.values, "%02X", c);

	return returnValue;
}

Hex4Bytes intHex4(unsigned short int i)
{
	Hex4Bytes returnValue = { 0 };
#pragma warning(disable: 4996)
	sprintf(returnValue.values, "%04X", i);

	return returnValue;
}