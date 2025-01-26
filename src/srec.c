/*
* FILE:				srec.c
* PROJECT:			SENG2030 - encodeInput Assignment #2
* PROGRAMMER:		Tino Restivo, Olha Mezin
* FIRST VERSION:	Jan 23, 2025
* DESCRIPTION:
*
* This file contains logic for generating the S19 file
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../inc/srec.h"
/*
	Function: int srecFile(FILE* inputFile, FILE* outputFile)

	Parameters:		FILE* inputFile:		The input file pointer
					FILE* outputFile:		The output file pointer
	Return Value:	int status:				int (result Success or Error)

	Description: This function generates the srecFile / or stdout.

*/
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
/*
	Function: void srecAddS0Record(FILE* outputFile)

	Parameters:		FILE* outputFile:		The output file pointer

	Return Value:	void

	Description: This function generates data for the S0 record.

*/
void srecAddS0Record(FILE* outputFile)
{
	unsigned char calcLength = OUR_NAMES_LENGTH + (A_FIELD + M_FIELD) / 2;

	Hex2Bytes cfield = charHex2(calcLength);

	Location location0 = { 0,{'0','0','0','0'} };

	Hex2Bytes mfield = createCheckSum(calcLength, location0.locationValue, OUR_NAMES, OUR_NAMES_LENGTH);

	SLine s = { S0,cfield.values,location0.hex.values,OUR_NAMES,OUR_NAMES_LENGTH,mfield.values };

	writeSLine(s, outputFile);
}
/*
	Function: void srecAddS1Record(FILE* outputFile)

	Parameters:
					Location location:		Indicates what location (where this record starts)
					unsigned char* data:	The data for the Srecord
					int size:				The amount of data for the Srecord
					FILE* outputFile:		The output file pointer

	Return Value:	void

	Description: This function generates data for the S1 record.

*/
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
/*
	Function: void srecAddS5Record(int numOfS1Lines, FILE* outputFile)

	Parameters:
					int numOfS1Lines:		Indicates how many S1 lines were written to
					FILE* outputFile:		The output file pointer

	Return Value:	void

	Description: This function generates data for the S5 record.

*/
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
/*
	Function: void srecAddS9Record(FILE* outputFile)

	Parameters:
					FILE* outputFile:		The output file pointer

	Return Value:	void

	Description: This function generates data for the S9 record.

*/
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
/*
	Function: void writeSLine(SLine s, FILE* outputFile)

	Parameters:
					SLine s:		The SLine containing what to write

	Return Value:	void

	Description: This function writes the S record to the srecFile / or stdout.

*/
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
/*
	Function: Hex2Bytes createCheckSum(unsigned char count, unsigned short int address, unsigned char* data, int dataSize)

	Parameters:
					unsigned char count:			Count of data for record
					unsigned short int address:		Address for record
					unsigned char* data:			data values for record
					int dataSize:					Amount of data for record

	Return Value:	Hex2Bytes The 2 hex bytes that make up check sum

	Description: This function calculates the records checksum.

*/
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
/*
	Function: unsigned short int getDataSum(unsigned char* data, int dataSize)

	Parameters:
					unsigned char* data:			data values for record
					int dataSize:					Amount of data for record

	Return Value:	unsigned short int returns the sum of data

	Description: This function calculates the sum of all the data values (used for check sum).

*/
unsigned short int getDataSum(unsigned char* data, int dataSize)
{
	unsigned short int sum = 0;
	for (int i = 0; i < dataSize; i++)
	{
		sum = sum + data[i];
	}
	return sum;
}
/*
	Function: Hex2Bytes charHex2(unsigned char c)

	Parameters:
					unsigned char c:			The char value to convert to 2 bytes of hex

	Return Value:	Hex2Bytes The 2 hex bytes that is generated by the char value

	Description: This function generates 2 hex bytes from a single char value.

*/
Hex2Bytes charHex2(unsigned char c)
{
	Hex2Bytes returnValue = { 0 };
#pragma warning(disable: 4996)
	sprintf(returnValue.values, "%02X", c);

	return returnValue;
}
/*
	Function: Hex4Bytes intHex4(unsigned short int i)

	Parameters:
					unsigned short int i:			The int value to convert to 4 bytes of hex

	Return Value:	Hex4Bytes The 4 hex bytes that is generated by the int value

	Description: This function generates 4 hex bytes from a int value.

*/
Hex4Bytes intHex4(unsigned short int i)
{
	Hex4Bytes returnValue = { 0 };
#pragma warning(disable: 4996)
	sprintf(returnValue.values, "%04X", i);

	return returnValue;
}