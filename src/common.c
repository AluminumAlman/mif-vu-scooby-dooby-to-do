#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mvsdtd.h"
#include "common.h"

void *reallocCustom(void *pointer, size_t size)
{
        void *temp = malloc(size);
        if(temp != NULL)
        {
                memcpy(temp, pointer, size);
        }
        free(pointer);
        return(temp);
}

Task *convertStringToTask(const char *inputString)
{
        if(inputString == NULL)
        {
                return(NULL);
        }

        char *inputCopy = strdup(inputString);
        if(inputCopy == NULL)
        {
                return(NULL);
        }

        char *taskName = strtok(inputCopy, "#");
        char *taskDescription = strtok(NULL, "#");
        if(taskName == NULL || taskDescription == NULL)
        {
                free(inputCopy);
                return(NULL);
        }

        unsigned short int taskTime;
        unsigned char taskState;
        if(sscanf(taskDescription + strlen(taskDescription) + 1, "%4hu#%1hhu", &taskTime, &taskState) != 2)
        {
                free(inputCopy);
                return(NULL);
        }

        Task *newTask = createTask(taskName, taskDescription, taskTime, taskState);
        free(inputCopy);
        return(newTask);
}

char *convertTaskToString(const Task *inputTask)
{
        if(inputTask == NULL)
        {
                return(NULL);
        }

        // We'll allocate a character array (string) large enough to fit the name,
        // description, 3 '#' characters and 5 numeral (0~9) characters,
        // as well as a null terminator character
        char *newString = malloc(alignNumberToMemory((strlen(inputTask->name)
                                        + strlen(inputTask->description) + 9)));
        if(newString == NULL)
        {
                return(NULL);
        }

        int sprintReturn = sprintf(newString, "%s#%s#%hu#%hhu",
                        inputTask->name, inputTask->description,
                        inputTask->timeMins % MINUTES_IN_DAY,
                        inputTask->state % 2);
        if(sprintReturn < 0)
        {
                free(newString);
                return(NULL);
        }

        return(newString);
}

Task *convertStringToTaskArray(const char *inputString, size_t *retArrayCount)
{
        if(inputString == NULL || retArrayCount == NULL)
        {
                return(NULL);
        }

        char *inputCopy = strdup(inputString);
        if(inputCopy == NULL)
        {
                return(NULL);
        }

        char *splitString = strtok(inputCopy, "\n");
        if(splitString == NULL)
        {
                free(inputCopy);
                return(NULL);
        }

        size_t arrayCount = 0;
        size_t arrayCapacity = alignNumberToMemory(1);
        const size_t TASK_SIZE = alignNumberToMemory(sizeof(Task));

        Task *newArray = malloc(TASK_SIZE * arrayCapacity);
        if(newArray == NULL)
        {
                free(inputCopy);
                return(NULL);
        }

        Task *newTask = convertStringToTask(splitString);
        if(newTask != NULL)
        {
                memcpy(newArray + arrayCount, newTask, TASK_SIZE);
                free(newTask);
                ++arrayCount;
        }

        while((splitString = strtok(splitString + strlen(splitString) + 1, "\n")) != NULL)
                // Why not strtok(NULL, "\n")?
                // That's because convertStringToTask uses strtok,
                // which makes strtok forget the address to splitString every time
        {
                if(arrayCount >= arrayCapacity)
                {
                        arrayCapacity = alignNumberToMemory(arrayCapacity + 1);
                        newArray = realloc(newArray, TASK_SIZE * arrayCapacity);
                }
                newTask = convertStringToTask(splitString);
                if(newTask != NULL)
                {
                        memcpy(newArray + arrayCount, newTask, TASK_SIZE);
                        free(newTask);
                        ++arrayCount;
                }
        }
        *retArrayCount = arrayCount;

        free(inputCopy);
        return(newArray);
}

char *convertTaskArrayToString(const Task inputArray[], const size_t arrayCount)
{
        size_t newStringLength = 0;
        for(size_t i = 0; i < arrayCount; ++i)
        {
                newStringLength += strlen(inputArray[i].name);
                newStringLength += strlen(inputArray[i].description);
        }

        newStringLength += 9 * arrayCount;      // Each task struct gets written down in format
                                                // %s#%s#%4hu#%1hhu\n

        char *newString = malloc(alignNumberToMemory(sizeof(char) * newStringLength + 1));
        if(newString == NULL)
        {
                return(NULL);
        }

        char *stringPosition = newString;
        for(size_t i = 0; i < arrayCount; ++i)
        {
                int sprintResult = sprintf(stringPosition, "%s#%s#%hu#%hhu\n",
                                inputArray[i].name, inputArray[i].description,
                                inputArray[i].timeMins, inputArray[i].state);
                if(sprintResult < 0)
                {
                        free(newString);
                        return(NULL);
                }

                stringPosition += sprintResult;
        }
        newString[newStringLength] = 0;

        return(newString);
}

Task *createTask(char name[], char description[], unsigned int timeMins, unsigned char state)
{
        if(name == NULL || description == NULL)
        {
                return(NULL);
        }
        Task *newTask = malloc(alignNumberToMemory(sizeof(Task)));
        if(newTask == NULL)
        {
                return(NULL);
        }

        newTask->name = strdup(name);
        if(newTask->name == NULL)
        {
                free(newTask);
                return(NULL);
        }
        newTask->description = strdup(description);
        if(newTask->description == NULL)
        {
                free(newTask->name);
                free(newTask);
                return(NULL);
        }
        newTask->timeMins = timeMins % MINUTES_IN_DAY;
        newTask->state = state % 2;

        return(newTask);
}
void destroyTask(Task **inputTask)
{
        Task *tempTask = *inputTask;
        free(tempTask->name);
        free(tempTask->description);
        free(tempTask);
        *inputTask = NULL;
        return;
}
