#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "mvsdtd.h"

int main()
{
	char *testSubstituteBuffer[] = {"hi", "hey", "home", "hello"};
	char *pointerToSubstitutedTestBuffer;
	// hi
	pointerToSubstitutedTestBuffer = getSubstitutedString("${0}", 1, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hi") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${0}${0}", 1, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hihi") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${0}${0}${0}", 1, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hihihi") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${0}${0}${0}${0}", 1, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hihihihi") == 0);
	free(pointerToSubstitutedTestBuffer);
	// hey
	pointerToSubstitutedTestBuffer = getSubstitutedString("${1}", 2, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hey") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${1}${1}", 2, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "heyhey") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${1}${1}${1}", 2, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "heyheyhey") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${1}${1}${1}${1}", 2, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "heyheyheyhey") == 0);
	free(pointerToSubstitutedTestBuffer);
	// home
	pointerToSubstitutedTestBuffer = getSubstitutedString("${2}", 3, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "home") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${2}${2}", 3, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "homehome") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${2}${2}${2}", 3, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "homehomehome") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${2}${2}${2}${2}", 3, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "homehomehomehome") == 0);
	free(pointerToSubstitutedTestBuffer);
	// hello
	pointerToSubstitutedTestBuffer = getSubstitutedString("${3}", 4, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hello") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${3}${3}", 4, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hellohello") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${3}${3}${3}", 4, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hellohellohello") == 0);
	free(pointerToSubstitutedTestBuffer);
	pointerToSubstitutedTestBuffer = getSubstitutedString("${3}${3}${3}${3}", 4, testSubstituteBuffer);
	assert(strcmp(pointerToSubstitutedTestBuffer, "hellohellohellohello") == 0);
	free(pointerToSubstitutedTestBuffer);
	printf("Tests passed successfully!\n");
	return(EXIT_SUCCESS);
}
