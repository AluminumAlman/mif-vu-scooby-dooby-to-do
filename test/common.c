#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mvsdtd.h"
#include "common.h"

int main()
{
        printf("Testing convertStringToTask...\n");

        char testString[] = "vardas#aprasas#2#1";
        Task *testTask = convertStringToTask(testString);

        assert(!strcmp(testTask->name, "vardas"));
        assert(!strcmp(testTask->description, "aprasas"));
        assert(testTask->time == 2);
        assert(testTask->state == 1);

        printf("Testing convertTaskToString...\n");

        assert(!strcmp(testString, convertTaskToString(testTask)));

        printf("All tests passed successfully!\n");

        destroyTask(testTask);
        return(EXIT_SUCCESS);
}
