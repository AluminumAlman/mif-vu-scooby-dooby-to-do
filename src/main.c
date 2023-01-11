#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "enumstring.h"
#include "mvsdtd.h"
#include "taskadd.h"
#include "taskmark.h"
#include "taskremove.h"

///
/// CONSTANTS
///
const char USAGE_INFO[] = "Usage: %s [option] [task name]\n"
"\n"
"Options:\n"
"    add   Add a task with description within <filename here>\n"
"    rem   Remove a task from tracking\n"
"    mark  Mark a task as (un)finished\n"
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

        switch(GetOption(argv[1]))
        {
                case(add):
                        TaskAdd(argv[2]);
                        break;
                case(rem):
                        TaskRemove(argv[2]);
                        break;
                case(mark):
                        TaskMark(argv[2]);
                        break;
                default:
                        printf(USAGE_INFO, argv[0]);
                        return(EXIT_FAILURE);
        }

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
