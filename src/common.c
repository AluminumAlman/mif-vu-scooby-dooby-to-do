#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

Task *convertStringToTask(char *inputString)
{
        Task *newTask = malloc(alignNumberToMemory(sizeof(Task)));

        newTask->name = strtok(inputString, "#");
        newTask->description = strtok(NULL, "#");

        sscanf(strtok(NULL, "#"), "%hu", &(newTask->time));

        char *stateBuffer = strtok(NULL, "#");
        newTask->state = stateBuffer[0] - '0';


        return(NULL);
}

char *convertTaskToString(Task *inputTask)
{
        return(NULL);
}
