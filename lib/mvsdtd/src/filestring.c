#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "memalign.h"

size_t getFileSize(FILE *file)
{
	size_t fileSize,
               oldPosition = ftell(file);
	if(oldPosition == (size_t)-1)
		return(0);

	fseek(file, 0, SEEK_END);
	fileSize = ftell(file);
	fseek(file, oldPosition, SEEK_SET);

	return(fileSize);
}

char *readFileToString(char *const fileName)
{
	FILE *inputFile = fopen(fileName, "rb");
	if(inputFile == NULL)
		return(NULL);

	size_t fileSize = getFileSize(inputFile);

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
	for(size_t i = strlen(sourceString); i != (size_t)-1; --i)
		destinationString[i] = sourceString[i];

	return(destinationString);
}

char* replaceStringTokenWithSubstitute(char *stringTokenStart, size_t stringTokenLength, char *const tokenSubstituteString)
{
	size_t tokenSubstituteLength = strlen(tokenSubstituteString);

	if(stringTokenLength < tokenSubstituteLength) // Expand the string to correctly fit the substitute
		stringCopyInvertedDirection(stringTokenStart+tokenSubstituteLength, stringTokenStart+stringTokenLength);
	else if(stringTokenLength > tokenSubstituteLength) // Shrink the string to correctly fit the substitute
		stringCopy(stringTokenStart+tokenSubstituteLength, stringTokenStart+stringTokenLength);

	memcpy(stringTokenStart, tokenSubstituteString, tokenSubstituteLength); // Perform the substitution
	return(stringTokenStart);
}


char *getSubstitutedString(char const *sourceString, size_t substituteCount, char *const substituteStrings[])
{
	if(substituteStrings == NULL)
		return(NULL);

	// Calculate the sum of all string lengths, which is used for memory allocation
	size_t newStringLength = strlen(sourceString);
	for(size_t i = 0; i < substituteCount; ++i)
		if(substituteStrings[i] != NULL)
			newStringLength += strlen(substituteStrings[i]);

	char *newString = malloc(alignNumberToMemory(newStringLength+1));
	if(newString == NULL)
		return(NULL);
	strcpy(newString, sourceString);
	
	// Search for and perform substitutions
	char needleString[32] = "";
	for(size_t i = 0; i < substituteCount; ++i)
	{
		if(substituteStrings[i] == NULL)
			continue;

		// Search setup
		sprintf(needleString, "${%lu}", i);
		size_t needleStringLength = strlen(needleString);
		char *newStringPosition = newString;

		// Search and substitute loop
		while((newStringPosition = strstr(newStringPosition, needleString)) != NULL)
			replaceStringTokenWithSubstitute(newStringPosition, needleStringLength, substituteStrings[i]);
	}

	return(newString);
}
