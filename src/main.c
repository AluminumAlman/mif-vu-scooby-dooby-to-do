#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"
#include "enumstring.h"
#include "mvsdtd.h"
#include "taskadd.h"
#include "taskmark.h"
#include "taskremove.h"

///
/// CONSTANTS
///
const char USAGE_INFO[] = "Usage: %s [option] [option arguments]\n"
"\n"
"Options:\n"
"    add [file name]   Add a task with description within the file\n"
"    rem [task name]   Remove a task of the supplied name from the list\n"
"    mark [task name]  Toggle a task as either finished or unfinished\n"
"\n"
"Every option updates the task list \"TaskList.txt\" and HTML document \"index.html\"\n"
"Preferrably used in the same directory as the root directory of the project\n";

#define OPTIONS(FUNC) \
        FUNC(add) \
        FUNC(rem) \
        FUNC(mark) \
        FUNC(NULL_OPTION)

#define OPTIONS_COUNT 3

enum OPTIONS_ENUM {
        OPTIONS(GENERATE_ENUM)
};
const char OPTIONS_STRINGS[][16] = {OPTIONS(GENERATE_STRING)};

///
/// FUNCTION DEFINITIONS
///
static unsigned char GetOption(char *arg);
int sortTasksFunc(const void *a, const void *b);

///
/// MAIN
///
int main(int argc, char *argv[])
{
        if(argc != 3)
        {
                printf(USAGE_INFO, argv[0]);
                return(EXIT_FAILURE);
        }

        unsigned char gotOption = GetOption(argv[1]);
        if(gotOption >= OPTIONS_COUNT)
        {
                printf(USAGE_INFO, argv[0]);
                return(EXIT_FAILURE);
        }

        // Parse the saved tasks into memory as a task struct array
        char *tasksFileContents = readFileToString("tasks.txt");
        Task *tasksArray = NULL;
        size_t tasksArrayCount = 0;
        if(tasksFileContents != NULL) // If the file was read successfully,
        {
                // turn the string into an array of tasks
                tasksArray = convertStringToTaskArray(tasksFileContents, &tasksArrayCount);
                free(tasksFileContents); // Then get rid of string
        }

        switch(GetOption(argv[1]))
        {
                case(add):
                {
                        if(tasksArrayCount == 0 || alignNumberToMemory(tasksArrayCount) != alignNumberToMemory(tasksArrayCount + 1))
                                // In case we don't have enough space to add a task to the array,
                                // reallocate it with increased size
                        {
                                tasksArray = realloc(tasksArray,
                                                alignNumberToMemory(sizeof(Task)) *
                                                alignNumberToMemory(tasksArrayCount + 1));
                        }
                        if(TaskAdd(argv[2], tasksArray, tasksArrayCount))
                        {
                                ++tasksArrayCount;
                        }
                        else
                        {
                                printf("Failed to add task from file \"%s\"\n", argv[2]);
                        }
                        break;
                }
                case(rem):
                {
                        if(TaskRemove(tasksArray, tasksArrayCount, argv[2]))
                        {
                                --tasksArrayCount;
                        }
                        else
                        {
                                printf("Failed to remove task of name \"%s\" from tasks list\n", argv[2]);
                        }
                        break;
                }
                case(mark):
                {
                        if(TaskMark(argv[2], tasksArray, tasksArrayCount) == 0)
                        {
                                printf("Failed to mark task of name \"%s\" within the tasks list\n", argv[2]);
                        }
                        break;
                }
                default:
                {
                        printf(USAGE_INFO, argv[0]);
                        return(EXIT_FAILURE);
                }
        }

        // Sort the tasks array
        qsort(tasksArray, tasksArrayCount, sizeof(Task), sortTasksFunc);

        // Save the modified task struct array to file
        char *tasksArrayAsString = convertTaskArrayToString(tasksArray, tasksArrayCount);
        writeStringToFile(tasksArrayAsString, "tasks.txt");

        free(tasksArrayAsString);
        free(tasksArray);
        return(EXIT_SUCCESS);
}

///
/// FUNCTION IMPLEMENTATIONS
///
static unsigned char GetOption(char *arg)
{
        for(unsigned char i = 0; i < OPTIONS_COUNT && i < 255; ++i)
        {
                if(strcmp(arg, OPTIONS_STRINGS[i]) == 0)
                {
                        return(i);
                }
        }
        return(NULL_OPTION);
}

int sortTasksFunc(const void *a, const void *b)
{
        const Task *aTask = a;
        const Task *bTask = b;
        if(aTask->state != bTask->state)
        {
                return(aTask->state - bTask->state);
        }
        return(aTask->timeMins - bTask->timeMins);
}

