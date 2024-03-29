#ifndef COMMON_H
#define COMMON_H

#define MINUTES_IN_DAY 1440

/**
 * Task struct
 * Houses the task's name, description, time and state
 */
typedef struct {
        char *name;
        char *description;
        unsigned short int timeMins; // Max of this should be MINUTES_IN_DAY
        unsigned char state; // Max of this should be 1
} Task;

/**
 * combineStrings
 * Combines two strings into one. AUTOMATICALLY FREES BOTH
 * @param  destination - the string on the left
 * @param  source - the string on the right
 * @return NULL on failure or a new address to a combined string.
 */
char *combineStrings(char *left, char *right);

/**
 * reallocCustom
 * Custom implementation of realloc, because in my experience it sometimes fails to actually allocate memory
 * AUTOMATICALLY FREES THE SUPPLIED POINTER
 * @param  pointer - pointer to reallocate
 * @param  size - size of new memory to allocate
 * @return address of newly allocated memory or NULL
 */
void *reallocCustom(void *pointer, size_t size);

/**
 * convertStringToTask
 * @param  inputString - string to turn into a task struct
 * @return pointer to a new task struct or NULL on failure
 */
extern Task *convertStringToTask(const char *inputString);

/**
 * convertTaskToString
 * @param  inputTask - task to turn into a string
 * @return pointer to a new string or NULL on failure
 */
extern char *convertTaskToString(const Task *inputTask);

/**
 * convertStringToTaskArray
 * @param  inputString - string to turn into a task struct array
 * @param  retArrayCount - address to a variable which is used to store the amount of elements within the array
 * @return pointer to a new task struct or NULL on failure
 */
extern Task *convertStringToTaskArray(const char *inputString, size_t *retArrayCount);

/**
 * convertTaskArrayToString
 * @param  inputArray - tasks to be converted into a string
 * @param  arrayCount - how many elements are within the input array
 * @return pointer to a new string or NULL on failure
 */
extern char *convertTaskArrayToString(const Task inputArray[], const size_t arrayCount);

/**
 * createTask
 * @param  name - the task's name
 * @param  description - the task's description
 * @param  timeMins - the time of the task in minutes
 * @param  state - 0 (not marked) or 1 (marked);
 * @return newly created task struct
 */
Task *createTask(char name[], char description[], unsigned int timeMins, unsigned char state);

/**
 * destroyTask
 * @param  inputTask - task to destroy (and free up its memory)
 */
extern void destroyTask(Task **inputTask);

#endif
