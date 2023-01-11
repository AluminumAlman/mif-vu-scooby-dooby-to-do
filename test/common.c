#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "mvsdtd.h"
#include "common.h"

int main()
{
        // Base function tests
        printf("Testing convertStringToTask...\n");

        char testString[] = "vardas#aprasas#2#1";
        Task *testTask = convertStringToTask(testString);
        if(testTask == NULL)
        {
                printf("Failed to allocate the test task...\n");
                return(EXIT_FAILURE);
        }

        assert(!strcmp(testTask->name, "vardas"));
        assert(!strcmp(testTask->description, "aprasas"));
        assert(testTask->timeMins == 2);
        assert(testTask->state == 1);

        printf("Testing convertTaskToString...\n");

        assert(!strcmp(testString, convertTaskToString(testTask)));

        destroyTask(&testTask);
        assert(testTask == NULL);

        // Array function tests
        printf("Testing convertStringToTaskArray...\n");

        char testArrayString[] = "vardas1#aprasas1#0#0\n"
                "vardas2#aprasas2#1#1\n"
                "vardas3#aprasas3#2#0\n"
                "vardas4#aprasas4#3#1\n"
                "vardas5#aprasas5#4#0\n"
                "vardas6#aprasas6#5#1\n"
                "vardas7#aprasas7#6#0\n"
                "vardas8#aprasas8#7#1\n"
                "vardas9#aprasas9#8#0\n"
                "vardas10#aprasas10#9#1\n"
                "vardas11#aprasas11#10#0\n"
                "vardas12#aprasas12#11#1\n"
                "vardas13#aprasas13#12#0\n"
                "vardas14#aprasas14#13#1\n";
        size_t arrayCap = 0;
        Task *testTaskArray = convertStringToTaskArray(testArrayString, &arrayCap);
        if(testTaskArray == NULL)
        {
                printf("Failed to allocate the test task array...\n");
                return(EXIT_FAILURE);
        }

        assert(strcmp(testTaskArray[0].name, "vardas1") == 0);
        assert(strcmp(testTaskArray[0].description, "aprasas1") == 0);
        assert(testTaskArray[0].timeMins == 0);
        assert(testTaskArray[0].state == 0);

        assert(strcmp(testTaskArray[1].name, "vardas2") == 0);
        assert(strcmp(testTaskArray[1].description, "aprasas2") == 0);
        assert(testTaskArray[1].timeMins == 1);
        assert(testTaskArray[1].state == 1);

        assert(strcmp(testTaskArray[2].name, "vardas3") == 0);
        assert(strcmp(testTaskArray[2].description, "aprasas3") == 0);
        assert(testTaskArray[2].timeMins == 2);
        assert(testTaskArray[2].state == 0);

        assert(strcmp(testTaskArray[3].name, "vardas4") == 0);
        assert(strcmp(testTaskArray[3].description, "aprasas4") == 0);
        assert(testTaskArray[3].timeMins == 3);
        assert(testTaskArray[3].state == 1);

        assert(strcmp(testTaskArray[4].name, "vardas5") == 0);
        assert(strcmp(testTaskArray[4].description, "aprasas5") == 0);
        assert(testTaskArray[4].timeMins == 4);
        assert(testTaskArray[4].state == 0);

        assert(strcmp(testTaskArray[5].name, "vardas6") == 0);
        assert(strcmp(testTaskArray[5].description, "aprasas6") == 0);
        assert(testTaskArray[5].timeMins == 5);
        assert(testTaskArray[5].state == 1);

        assert(strcmp(testTaskArray[6].name, "vardas7") == 0);
        assert(strcmp(testTaskArray[6].description, "aprasas7") == 0);
        assert(testTaskArray[6].timeMins == 6);
        assert(testTaskArray[6].state == 0);

        assert(strcmp(testTaskArray[7].name, "vardas8") == 0);
        assert(strcmp(testTaskArray[7].description, "aprasas8") == 0);
        assert(testTaskArray[7].timeMins == 7);
        assert(testTaskArray[7].state == 1);

        assert(strcmp(testTaskArray[8].name, "vardas9") == 0);
        assert(strcmp(testTaskArray[8].description, "aprasas9") == 0);
        assert(testTaskArray[8].timeMins == 8);
        assert(testTaskArray[8].state == 0);

        assert(strcmp(testTaskArray[9].name, "vardas10") == 0);
        assert(strcmp(testTaskArray[9].description, "aprasas10") == 0);
        assert(testTaskArray[9].timeMins == 9);
        assert(testTaskArray[9].state == 1);

        assert(strcmp(testTaskArray[10].name, "vardas11") == 0);
        assert(strcmp(testTaskArray[10].description, "aprasas11") == 0);
        assert(testTaskArray[10].timeMins == 10);
        assert(testTaskArray[10].state == 0);

        assert(strcmp(testTaskArray[11].name, "vardas12") == 0);
        assert(strcmp(testTaskArray[11].description, "aprasas12") == 0);
        assert(testTaskArray[11].timeMins == 11);
        assert(testTaskArray[11].state == 1);

        assert(strcmp(testTaskArray[12].name, "vardas13") == 0);
        assert(strcmp(testTaskArray[12].description, "aprasas13") == 0);
        assert(testTaskArray[12].timeMins == 12);
        assert(testTaskArray[12].state == 0);

        assert(strcmp(testTaskArray[13].name, "vardas14") == 0);
        assert(strcmp(testTaskArray[13].description, "aprasas14") == 0);
        assert(testTaskArray[13].timeMins == 13);
        assert(testTaskArray[13].state == 1);

        assert(arrayCap == 14);

        printf("Testing convertTaskArrayToString...\n");

        char *stringToTaskReturn = convertTaskArrayToString(testTaskArray, arrayCap);
        if(stringToTaskReturn == NULL)
        {
                printf("Failed to allocate the return string while trying to convert test array...\n");
                return(EXIT_FAILURE);
        }
        assert(strcmp(stringToTaskReturn, testArrayString) == 0);

        printf("All tests passed successfully!\n");

        return(EXIT_SUCCESS);
}
