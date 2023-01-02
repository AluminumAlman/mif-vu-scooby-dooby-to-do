#ifndef COMMON_H
#define COMMON_H

#include <inttypes.h>

typedef struct {
        char *name;
        char *description;
        uint16_t time;
        unsigned char state;
} Task;

Task *convertStringToTask(char *inputString);

char *convertTaskToString(Task *inputTask);

#endif
