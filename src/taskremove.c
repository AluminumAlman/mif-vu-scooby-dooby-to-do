#include <string.h>
#include "taskremove.h"

int TaskRemove (Task taskArray[], int size, const char *taskToDeleteName ){      //funkcija grazina sekmes atveju 1, nesekmes 0 
        int position;
        int flag = 0;           //flagas skirtas patikrinti, ar buvo rastas task'as, kuri reikia istrinti 
        for(int i = 0; i < size; ++i){
                if(strcmp(taskArray[i].name, taskToDeleteName ) == 0){
                        position = i;
                        flag = 1;
                        break;
                }
                   
        }
        if(!flag)
                return 0;      //masyve nebuvo rasta reikiamo task'o

        for(int i = position; i < size - 1; ++i){
                taskArray[i] = taskArray[i + 1];  
        }
        return 1;               //taskas buvo sekmingai istrintas
}
// size main'e turi sumazeti
