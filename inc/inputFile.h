#pragma warning(disable: 4996) // required by Visual Studio for fopen().

// Constants
#define LOCATION 2048
#define ERROR 1

// Prototypes
int inputFileRead(char* fileName, FILE** inputFile);

int asm(FILE* inputFile, FILE* outputFile);