#include "cpu.h"
#include "../config.h"
#include "../globals.h"
#include "../scheduler/scheduler.h"
#include "../io/io.h"
#include "../stats/stats.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void* cpu_thread(void* arg){
    (void) arg;

    while(atomic_load(&system_running)){
        sem_wait(&sem_cpu);
    
        if(!atomic_load(&system_running)) break;

        PCB* process = scheduler_getRunning();

        if(!process){
            #if DEBUG
                printf("[CPU] Nenhum processo para executar\n");
            #endif
            continue;
        }

        #if DEBUG
            printf("[CPU] Executando PID %d\n", PCB_getId(process));
        #endif

        int quantum = 0;
        int blocked = 0;

        while(quantum < QUANTUM && PCB_getRemainingTime(process) > 0){
            usleep(TICK_MS*1000);

            PCB_DecreaseRemainingTime(process);
            quantum++;
            stats_on_running(process);

            #if DEBUG
                printf("[CPU] PID %d | restante=%d | q=%d\n", PCB_getId(process), PCB_getRemainingTime(process), quantum);
            #endif

            if(rand() % 10 < 1){
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