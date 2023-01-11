#include <stdio.h>
#include <stdlib.h>
#include "taskadd.h"
#include "common.h"
#include "mvsdtd.h"


char TaskAdd(char argumentFile[], Task allTasks[], int newTaskIndex)
{
        FILE *argument = fopen(argumentFile, "r");
        char argumentStr[getFileSize(argument) + 1];

        if (argument == NULL)
                return 0;
        
        int i = 0;
        int sizeOfFile = getFileSize(argument);
        while(i < sizeOfFile)
        {
                argumentStr[i] = fgetc(argument);
                i++;
        }
        argumentStr[i] = '\0';

        Task *newTask = convertStringToTask(argumentStr);
        if(newTask == NULL)
                return 0;
        
        allTasks[newTaskIndex] = *newTask;
        
        return 1;   
}
