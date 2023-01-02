 #ifndef LIBMVSDTD_H
 #define LIBMVSDTD_H
 #include <stdlib.h>
 #include <stdio.h>
 #include <string.h>
/*
 * @author Almantas Mecele
 * @version 0.1
 * Dummy header file to be expanded trough #include
 * DO NOT INCLUDE ANYWHERE IN ORIGINAL PROJECT
 */
       
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Aligns number to memory (rounds up to multiples of two, from a minimum of 8)
 * @param  number - number to be aligned
 * @return a number rounded up to nearest number from {8, 16, 32, 64, 128, 256, ...}
 */
size_t alignNumberToMemory(size_t number);
       
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Gets the file's size
 * @param  file - pointer to a FILE struct
 * @return filesize in bytes
 */
size_t getFileSize(FILE *file);
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Creates a new string which is filled by a file's contents.
 * @param  fileName - file name as string
 * @return file bytes as string
 */
char *readFileToString(char const *fileName);
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Writes a string to a file.
 * @param  sourceString - string to write to file
 * @param  fileName - file name as string
 */
void writeStringToFile(char *const sourceString, char *const fileName);
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Copies the source string to destination string from left to right.
 * @param  destinationString - strint to copy to
 * @param  sourceString - string to copy from
 * @return destinationString argument
 */
char* stringCopy(char *destinationString, char *const sourceString);
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Copies the source string to destination string from right to left.
 * @param  destinationString - string to copy to
 * @param  sourceString - string to copy from
 * @return destinationString argument
 */
char* stringCopyInvertedDirection(char *destinationString, char *const sourceString);
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Expands or shrinks the string containing the supplied string token start to fit the token substitute string, then writes the token substitute string to the start of the string token. DOES NOT ACTUALLY RESIZE THE STRING!
 * @param stringTokenStart - where the start of the string's token is
 * @param stringTokenLength - the string token's span
 * @param tokenSubstituteString - with what string to replace the token
 * @return stringTokenStart argument
 */
char* replaceStringTokenWithSubstitute(char *stringTokenStart, size_t stringTokenLength, char *const tokenSubstituteString);
/*
 * @author Almantas Mecele (AluminumAlman)
 * @since 0.1
 * Substitutes ${%d} tokens, where %d is a non-negative number, in a string with other strings.
 * @param  sourceString - string with ${%d} tokens
 * @param  substituteCount - count of how many tokens to substitute
 * @param  substituteStrings - strings with which to replace the tokens
 * @return new string with replaced substitution tokens
 */
char *getSubstitutedString(char *const sourceString, size_t substituteCount, char *const substituteStrings[]);
 #endif
