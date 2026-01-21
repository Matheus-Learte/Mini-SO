#ifndef __SCHEDULER__
    #define __SCHEDULER__

    #include "../pcb/pcb.h"

    void scheduler_init();
    void* scheduler_thread(void* arg);
    void scheduler_addReady(PCB * process);
    void scheduler_exitCPU(PCB* process);
    PCB* scheduler_getRunning(void);

#endif