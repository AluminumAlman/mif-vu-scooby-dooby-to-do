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

#if defined(_WIN32) || defined(_WIN64)

#define TASK_TEMPLATE_FILENAME "templates\\taskListElement.html"
#define INDEX_TEMPLATE_FILENAME "templates\\index.html"
#elif defined(unix)

#define TASK_TEMPLATE_FILENAME "templates/taskListElement.html"
#define INDEX_TEMPLATE_FILENAME "templates/index.html"
#endif

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
        if(tasksArrayAsString == NULL)
        {
                printf("Failed to allocate memory for the task array string\n");

                for(size_t i = 0; i < tasksArrayCount; ++i)
                {
                        free(tasksArray[i].name);
                        free(tasksArray[i].description);
                }
                free(tasksArray);
                return(EXIT_FAILURE);
        }
        writeStringToFile(tasksArrayAsString, "tasks.txt");
        free(tasksArrayAsString);

        //printf("%s\n", TASK_TEMPLATE_FILENAME); // TODO: remove this
        char *taskTemplate = readFileToString(TASK_TEMPLATE_FILENAME);
        if(taskTemplate == NULL)
        {
                printf("Failed to load the task html template at \"%s\"\n", TASK_TEMPLATE_FILENAME);

                for(size_t i = 0; i < tasksArrayCount; ++i)
                {
                        free(tasksArray[i].name);
                        free(tasksArray[i].description);
                }
                free(tasksArray);
                return(EXIT_FAILURE);
        }
        //printf("%s\n", taskTemplate); // TODO: remove this

        // Prepare the templated tasks array
        char **filledTemplatedTasksArray = malloc(sizeof(char*) * tasksArrayCount);
        if(filledTemplatedTasksArray == NULL)
        {
                printf("Failed to allocate memory for keeping track of templated strings\n");

                free(taskTemplate);
                for(size_t i = 0; i < tasksArrayCount; ++i)
                {
                        free(tasksArray[i].name);
                        free(tasksArray[i].description);
                }
                free(tasksArray);
                return(EXIT_FAILURE);
        }
        char firstSubstituteBuffer[16] = ""; // For storing time formatted as a string
                                 // and saving the count of finished tasks as a string
        char secondSubstituteBuffer[16] = ""; // For fitting yes.png
                                       // and saving the count of tasks as a string
        char *substituteStrings[4] = {NULL, firstSubstituteBuffer, secondSubstituteBuffer};

        // Fill the templated tasks array
        for(size_t i = 0; i < tasksArrayCount; ++i)
        {
                // Load the necessary strings into subsituteStrings
                substituteStrings[0] = tasksArray[i].name;
                sprintf(firstSubstituteBuffer, "%02hhu:%02hhu", (tasksArray[i].timeMins / 60) % 100, tasksArray[i].timeMins % 60);
                sprintf(secondSubstituteBuffer, "%s", tasksArray[i].state ? "yes.png" : "no.png");

                // Create a new templated string
                filledTemplatedTasksArray[i] = getSubstitutedString(taskTemplate, 3, substituteStrings);
                //printf("%s\n", filledTemplatedTasksArray[i]); // TODO: remove this
        }

        free(taskTemplate); // Get rid of the template once we've done all of the filling

        char *templatedTasksString = filledTemplatedTasksArray[0];
        filledTemplatedTasksArray[0] = NULL;
        for(size_t i = 1; i < tasksArrayCount; ++i)
        {
                templatedTasksString = combineStrings(templatedTasksString, filledTemplatedTasksArray[i]);
                if(templatedTasksString == NULL)
                {
                        break;
                }
                filledTemplatedTasksArray[i] = NULL;
        }
        if(templatedTasksString == NULL)
        {
                printf("Failed to combine templated tasks strings into one\n");

                for(size_t i = 0; i < tasksArrayCount; ++i) // Free the templated tasks array
                {
                        if(filledTemplatedTasksArray[i] == NULL) // Since it may have failed at any string,
                                                                 // skip over the strings which were used
                        {
                                continue;
                        }
                        free(filledTemplatedTasksArray[i]);
                }
                free(filledTemplatedTasksArray);
                for(size_t i = 0; i < tasksArrayCount; ++i)
                {
                        free(tasksArray[i].name);
                        free(tasksArray[i].description);
                }
                free(tasksArray);
                return(EXIT_FAILURE);
        }
        free(filledTemplatedTasksArray); // Since combineStrings already freed all of the strings within,
                                         // just need to free the array itself
        //printf("%s\n", templatedTasksString); // TODO: remove this

        // Create the index using the template
        char *indexTemplate = readFileToString(INDEX_TEMPLATE_FILENAME);
        if(indexTemplate == NULL)
        {
                printf("Failed to load the index template at \"%s\"\n", INDEX_TEMPLATE_FILENAME);

                for(size_t i = 0; i < tasksArrayCount; ++i)
                {
                        free(tasksArray[i].name);
                        free(tasksArray[i].description);
                }
                free(tasksArray);
                return(EXIT_FAILURE);
        }

        // Prepare for substitution
        substituteStrings[0] = templatedTasksString;
        substituteStrings[1] = tasksArray[0].description;
        substituteStrings[2] = firstSubstituteBuffer;
        size_t countOfMarkedTasks = 0;
        for(size_t i = 0; i < tasksArrayCount; ++i)
        {
                if(tasksArray[i].state == 0)
                {
                        continue;
                }
                ++countOfMarkedTasks;
        }
        sprintf(firstSubstituteBuffer, "%lu", countOfMarkedTasks);
        substituteStrings[3] = secondSubstituteBuffer;
        sprintf(secondSubstituteBuffer, "%lu", tasksArrayCount);
        char *indexTemplated = getSubstitutedString(indexTemplate, 4, substituteStrings); // Substitute
        printf("%s\n", indexTemplated); //TODO: remove this
        free(indexTemplate); // Free the template

        // Write the substituted template to the html file
        writeStringToFile(indexTemplated, "index.html");
        free(indexTemplated); // Free the substituted template

        for(size_t i = 0; i < tasksArrayCount; ++i)
        {
                free(tasksArray[i].name);
                free(tasksArray[i].description);
        }
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

