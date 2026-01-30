#include "pcb.h"
#include <stdlib.h>
#include <stdio.h>

struct pcb{
    int id;
    int total_time;
    int remaining_time;
    int arrival_time;
    STATE estado;
};

PCB* Create_process(int id, int total_time, int arrive_time){
    PCB* aux = (PCB*)malloc(sizeof(PCB));

    if(aux){
        aux->id = id;
        aux->total_time = total_time;
        aux->remaining_time = total_time;
        aux->arrival_time = arrive_time;
        aux->estado = NEW;
    }else
        printf("ALOCAÇÂO MAL SUCEDIDA.\n\n");

return aux;
}

int Delete_process(PCB** process){
    if(*process){
        free(*process);
        *process = NULL;
        return 1;
    }

return 0;
}

int Set_state(PCB* process, STATE state){
    if(process){
        process->estado = state;
        return 1;
    }

return 0;
}

int isFinished_process(const PCB* process){
    if(process){
        if(process->remaining_time == 0)
            return 1;
    }

return 0;
}

int PCB_setId(PCB* process, int id){
    if(process){
        process->id = id;

        return 1;
    }
return 0;
}

int PCB_setTotalTime(PCB* process, int total){
    if(process){
        process->total_time = total;

        return 1;
    }

return 0;
}

int PCB_DecreaseRemainingTime(PCB* process){
    if(process){
        if(process->remaining_time > 0){
            process->remaining_time--;
            return 1;
        }
    }

return 0;
}

int PCB_setEstado(PCB* process, STATE estado){
    if(process){
        process->estado = estado;

        return 1;
    }

return 0;
}

int PCB_getId(PCB* process){
    if(process){
        return process->id;
    }

return ERRO;
}

int PCB_getTotalTime(PCB* process){
    if(process){
        return process->total_time;
    }

return ERRO;
}

int PCB_getRemainingTime(PCB* process){
    if(process){
        return process->remaining_time;
    }

return ERRO;
}

int PCB_getArrivalTime(PCB* process){
    if(process){
        return process->arrival_time;   
    }

return ERRO;
}

STATE PCB_getEstado(PCB* process){
    if(process){
        return process->estado;   
    }

return NONE;
}