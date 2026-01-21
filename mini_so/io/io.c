#include "io.h"
#include "../globals.h"
#include "../config.h"
#include "../scheduler/scheduler.h"
#include "../pcb/pcb.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void io_init(){
    sem_init(&io_sem, 0, 0);
}

void* io_thread(void *arg){
    (void) arg;

    while(1){
        sem_wait(&io_sem);

        pthread_mutex_lock(&mutex_blocked);

        if(Queue_isEmpty(blocked)){
            pthread_mutex_unlock(&mutex_blocked);
            continue;
        }

        PCB* process = (PCB*) Front_queue(blocked);
        Remove_queue(blocked);

        pthread_mutex_unlock(&mutex_blocked);

        int io_time = ((rand() % 99) + 1) * 100000;

        #if DEBUG
            printf("[IO] PID %d em I/O por %d us\n", PCB_getId(process), io_time);
        #endif

        usleep(io_time);

        PCB_setEstado(process, READY);

        #if DEBUG
            printf("[IO] PID %d terminou I/O\n", PCB_getId(process));
        #endif

        scheduler_addReady(process);
    }

return NULL;
}