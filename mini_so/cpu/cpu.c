#include "cpu.h"
#include "../config.h"
#include "../globals.h"
#include "../scheduler/scheduler.h"
#include "../io/io.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* cpu_thread(void* arg){
    (void) arg;

    while(1){
        sem_wait(&sem_cpu);
    
        PCB* process = scheduler_getRunning();

        if(!process)
            continue;

        #if DEBUG
            printf("[CPU] Executando PID %d\n", PCB_getId(process));
        #endif

        int quantum = 0;
        int blocked = 0;

        while(quantum < QUANTUM && PCB_getRemainingTime(process) > 0){
            usleep(TICK_MS*1000);

            PCB_DecreaseRemainingTime(process);
            quantum++;

            #if DEBUG
                printf("[CPU] PID %d | restante=%d | q=%d\n", PCB_getId(process), PCB_getRemainingTime(process), quantum);
            #endif

            if(rand() % 10 < 3){
                #if DEBUG
                    printf("[IO] PID %d solicitou I/O\n", PCB_getId(process));
                #endif

                blocked = 1;
                break;
            }
        }

        if(!blocked){
            if(!PCB_getRemainingTime(process)){
                PCB_setEstado(process, TERMINATED);
            }else
                PCB_setEstado(process, READY);
        }else
            PCB_setEstado(process, BLOCKED);
        
        scheduler_exitCPU(process);
    }

return NULL;
}