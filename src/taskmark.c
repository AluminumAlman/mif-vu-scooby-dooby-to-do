#include <string.h>
#include "taskmark.h"
#include "common.h"

char TaskMark(char taskName[], Task taskList[], int taskAmount)
{
        unsigned char markFlag = 0;
        int i = 0;
        while(i < taskAmount && markFlag == 0)
        {
                if(strcmp(taskList[i].name, taskName) == 0)
                {
                        taskList[i].state = 1;
                        markFlag = 1;
                }
                i++;
        }

        if(markFlag == 1)
                return 1;
        else 
                return 0;
}
