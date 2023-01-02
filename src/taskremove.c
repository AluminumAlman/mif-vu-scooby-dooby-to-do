#include <string.h>
#include "common.h"


int TaskRemove (Task taskArray[], int size, Task taskToDelete ){       
        int position;
        
        for(int i = 0; i < size; ++i){
                if(strcmp(taskArray[i].name, taskToDelete.name ) == 0){
                        position = i;
                        break;
                }
                return -1;       
        }

        for(int i = position; i < size - 1; ++i){
                taskArray[i] = taskArray[i + 1];  
        }
        return 0;
}
// size maine turi sumazeti
