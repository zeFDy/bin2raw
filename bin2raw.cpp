// bin2raw.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>

int main(int argc, char* argv[])
{
#define DEFAULT_INPUT_FILENAME		"SdRamExec.bin"
#define	DEFAULT_OUTPUT_FILENAME		"SdRamExec.raw"
#define	SIZEOF_FILENAME				256

	uint8_t*	ucBuffer			= NULL;
	uint32_t	uiSize				= 0;
	uint32_t	uiOffset			= 0;
	FILE*		myFile				= 0;
	FILE*		myOutputFile		= 0;
	uint8_t*	ucOriginalBuffer	= NULL;
	char		caInputFileName[SIZEOF_FILENAME];
	char		caOutputFileName[SIZEOF_FILENAME];

	sprintf_s(caInputFileName, SIZEOF_FILENAME, DEFAULT_INPUT_FILENAME);
	sprintf_s(caOutputFileName, SIZEOF_FILENAME, DEFAULT_OUTPUT_FILENAME);

	if (argc >= 2)       // 1er argument (optionnel) est le fichier d'entree 
	{
		printf("argv[1]     = %s\n", argv[1]);
		printf("argv[1] len = %d\n", strlen(argv[1]));
		memset(caInputFileName, 0, SIZEOF_FILENAME);
		strncpy_s(caInputFileName, SIZEOF_FILENAME, argv[1], strlen(argv[1]));
	}

	if (argc >= 3)       // 2eme argument (optionnel) est le fichier de sortie
	{
		printf("argv[2]     = %s\n", argv[2]);
		printf("argv[2] len = %d\n", strlen(argv[2]));
		memset(caOutputFileName, 0, SIZEOF_FILENAME);
		strncpy_s(caOutputFileName, SIZEOF_FILENAME, argv[2], strlen(argv[2]));
	}

	// to do - here check input file presence



	fopen_s(&myFile, caInputFileName, "rb");
	if (myFile == NULL)	return -1;
	fseek(myFile, 0, SEEK_END);
	uiSize = ftell(myFile);
	fseek(myFile, 0, SEEK_SET);
	ucBuffer = (uint8_t*)malloc(uiSize+16);
	fread(ucBuffer, 1, uiSize, myFile);
	ucOriginalBuffer = ucBuffer;
	fclose(myFile);

	fopen_s(&myOutputFile, caOutputFileName, "wb");
	if (myOutputFile == NULL)	return -1;
	
	fprintf(myOutputFile, "RAW1");
	fwrite(&uiOffset,			1, sizeof(uint32_t),	myOutputFile);
	fwrite(&uiSize,				1, sizeof(uint32_t),	myOutputFile);
	fwrite(ucOriginalBuffer,	1, uiSize,				myOutputFile);


	fclose(myOutputFile);
}