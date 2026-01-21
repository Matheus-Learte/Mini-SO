#ifndef __PCB__
    #define __PCB__

    typedef enum{
        NEW, 
        READY,
        RUNNING,
        BLOCKED,
        TERMINATED,
        NONE
    }STATE;

    typedef struct pcb PCB;

    #define ERRO -32000

    PCB* Create_process(int id, int total_time, int arrive_time);
    int Delete_process(PCB** process);
    int Set_state(PCB* process, STATE state);
    int decrease_time(PCB* process);
    int isFinished_process(const PCB* process);

    int PCB_getId(PCB* process);
    int PCB_getTotalTime(PCB* process);
    int PCB_getRemainingTime(PCB* process);
    int PCB_getArrivalTime(PCB* process);
    STATE PCB_getEstado(PCB* process);

    int PCB_setId(PCB* process, int id);
    int PCB_setTotalTime(PCB* process, int total);
    int PCB_DecreaseRemainingTime(PCB* process);
    int PCB_setEstado(PCB* process, STATE estado);

#endif