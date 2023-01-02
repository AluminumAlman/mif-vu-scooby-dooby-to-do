#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mvsdtd.h"
#include "common.h"

Task *convertStringToTask(char *inputString)
{
        // Since strtok messes with the string, create a copy of it
        char *inputStringCopy = strcpy(malloc(alignNumberToMemory(strlen(inputString) + 1)), inputString);
        Task *newTask = malloc(alignNumberToMemory(sizeof(Task)));

        // Make sure we're passing off addresses to copies, not the input string itself
        char *tempString = strtok(inputStringCopy, "#");
        newTask->name = strcpy(malloc(alignNumberToMemory(strlen(tempString)+1)), tempString);

        tempString = strtok(NULL, "#");
        newTask->description = strcpy(malloc(alignNumberToMemory(strlen(tempString)+1)), tempString);

        sscanf(strtok(NULL, "#"), "%hu", &(newTask->time));

        char *stateBuffer = strtok(NULL, "#");
        newTask->state = stateBuffer[0] - '0';

        free(inputStringCopy); // Don't forget to free the copy

        return(newTask);
}

char *convertTaskToString(Task *inputTask)
{
        char *finalString = malloc(alignNumberToMemory(strlen(inputTask->name) +
                                strlen(inputTask->description) + 9));

        sprintf(finalString, "%s#%s#%hu#%hhu", inputTask->name, inputTask->description, inputTask->time, inputTask->state);

        return(finalString);
}

void destroyTask(Task *inputTask)
{
        free(inputTask->name);
        free(inputTask->description);
        free(inputTask);

        return;
}
