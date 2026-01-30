#include "io.h"
#include "../globals.h"
#include "../config.h"
#include "../scheduler/scheduler.h"
#include "../pcb/pcb.h"
#include "../stats/stats.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void io_init(){
    sem_init(&io_sem, 0, 0);
}

void* io_thread(void *arg){
    (void) arg;

    while(atomic_load(&system_running)){
        sem_wait(&io_sem);

        #if DEBUG
            printf("[IO] Thread acordou\n");
        #endif

        if(!atomic_load(&system_running)) break;

        // Processa todos os processos bloqueados disponíveis
        while(atomic_load(&system_running)) {
            pthread_mutex_lock(&mutex_blocked);

            if(Queue_isEmpty(blocked)){
                pthread_mutex_unlock(&mutex_blocked);
                break;
            }

            PCB* process = (PCB*) Front_queue(blocked);
            Remove_queue(blocked);
            
            pthread_mutex_unlock(&mutex_blocked);

            int io_time = ((rand() % 199) + 1) * 10000;

            #if DEBUG
                printf("[IO] PID %d em I/O por %d us\n", PCB_getId(process), io_time);
            #endif

            usleep(io_time);

            if(atomic_load(&system_running)) {
                stats_on_exit_blocked(process);
                PCB_setEstado(process, READY);
                stats_on_ready(process);

                #if DEBUG
                    printf("[IO] PID %d terminou I/O\n", PCB_getId(process));
                #endif

                scheduler_addReady(process);
            }
        }
    }

return NULL;
}