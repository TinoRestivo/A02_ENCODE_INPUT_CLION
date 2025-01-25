#pragma warning(disable: 4996) // required by Visual Studio for fopen().
// Constants
#define ARGS_COUNT 5
#define FILE_NAME 50
#define S_RECORD 2
#define ERROR 1

// Function prototypes
void printHelp(void);
int parseSwitches(int argc, char* argv[], char* inputFileName, char* outputFileName, int* outputFormat);