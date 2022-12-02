#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "memalign.h"

char *readFileToString(char *const fileName)
{
	FILE *inputFile = fopen(fileName, "rb");
	if(inputFile == NULL)
		return(NULL);

	fseek(inputFile, 0, SEEK_END);
	size_t fileSize = ftell(inputFile);
	fseek(inputFile, 0, SEEK_SET);

	char *newString = malloc(alignNumberToMemory(fileSize+1));
	if(newString == NULL)
		goto end;

	fread(newString, 1, fileSize, inputFile);
	newString[fileSize] = 0;

end:
	fclose(inputFile);
	return(newString);
}

void writeStringToFile(char *const sourceString, char *const fileName)
{
	FILE *outFile = fopen(fileName, "wb");
	if(outFile == NULL)
		return;

	fwrite(sourceString, 1, strlen(sourceString), outFile);

	fclose(outFile);
	return;
}

// """"Borrowed"""" from https://stackoverflow.com/questions/14476627/strcpy-implementation-in-c
char* stringCopy(char *destinationString, char *const sourceString)
{
	for(size_t i = 0; (destinationString[i] = sourceString[i]) != 0; ++i)
		;
	return(destinationString);
}

char* stringCopyInvertedDirection(char *destinationString, char *const sourceString)
{
	// Start copying from the right and proceed left
	for(size_t i = strlen(sourceString) + 1; i > 0; --i)
		destinationString[i-1] = sourceString[i-1];

	return(destinationString);
}

char* replaceStringTokenWithSubstitute(char *stringTokenStart, size_t stringTokenLength, char *const tokenSubstituteString)
{
	size_t tokenSubstituteLength = strlen(tokenSubstituteString);

	if(stringTokenLength < tokenSubstituteLength) // Expand the string to correctly fit the substitute
		stringCopyInvertedDirection(stringTokenStart+tokenSubstituteLength, stringTokenStart+stringTokenLength);
	else if(stringTokenLength > tokenSubstituteLength) // Shrink the string to correctly fit the substitute
		stringCopy(stringTokenStart+tokenSubstituteLength, stringTokenStart+stringTokenLength);

	memcpy(stringTokenStart, tokenSubstituteString, tokenSubstituteLength);
	return(stringTokenStart);
}


char *getSubstitutedString(char const *sourceString, size_t substituteCount, char *const substituteStrings[])
{
	// Calculate the new string length that would definitely fit everything
	size_t newStringLength = strlen(sourceString);
	if(substituteStrings != NULL)
		for(size_t i = 0; i < substituteCount; ++i)
			if(substituteStrings[i] != NULL)
				newStringLength += strlen(substituteStrings[i]);

	char *newString = malloc(alignNumberToMemory(newStringLength+1));
	if(newString == NULL)
		return(NULL);

	strcpy(newString, sourceString);

	if(substituteStrings == NULL)
		return(newString);


	char needleString[32] = "";
	for(size_t i = 0; i < substituteCount; ++i)
	{
		if(substituteStrings[i] == NULL)
			continue;

		sprintf(needleString, "${%lu}", i);
		size_t needleStringLength = strlen(needleString);
		char *newStringPosition = newString;

		while((newStringPosition = strstr(newStringPosition, needleString)) != NULL)
			replaceStringTokenWithSubstitute(newStringPosition, needleStringLength, substituteStrings[i]);
	}

	return(newString);
}
