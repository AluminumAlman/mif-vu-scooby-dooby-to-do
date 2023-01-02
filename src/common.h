#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>

typedef struct {
        char *name;
        char *description;
        unsigned short int time;
        unsigned char state;
} Task;

extern Task *convertStringToTask(char *inputString);

extern char *convertTaskToString(Task *inputTask);

#endif
