#ifndef COMMON_H
#define COMMON_H

typedef struct {
        char *name;
        char *description;
        unsigned short int time;
        unsigned char state;
} Task;

extern Task *convertStringToTask(char *inputString);

extern char *convertTaskToString(Task *inputTask);

extern void destroyTask(Task *inputTask);

#endif
