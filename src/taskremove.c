#pragma once
#include <string.h>
#include "common.h"
#include "taskremove.h"


int TaskRemove (Task taskArray[], int size, Task taskToDelete ){      //funkcija grazina sekmes atveju 0, nesekmes -1 
        int position;
        int flag = 0;           //flagas skirtas patikrinti, ar buvo rastas task'as, kuri reikia istrinti 
        for(int i = 0; i < size; ++i){
                if(strcmp(taskArray[i].name, taskToDelete.name ) == 0){
                        position = i;
                        flag = 1;
                        break;
                }
                   
        }
        if(!flag)
                return -1;      //masyve nebuvo rasta reikiamo task'o

        for(int i = position; i < size - 1; ++i){
                taskArray[i] = taskArray[i + 1];  
        }
        return 0;               //taskas buvo sekmingai istrintas
}
// size main'e turi sumazeti
