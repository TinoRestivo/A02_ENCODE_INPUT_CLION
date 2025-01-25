#pragma warning(disable: 4996) // required by Visual Studio for fopen().

// Constants
#define LOCATION 2048
#define ERROR 1
#define S_RECORD 2
// Prototypes
int outputFileRead(char* inputFileName, char* outputFileName, FILE** outputFile, int format);