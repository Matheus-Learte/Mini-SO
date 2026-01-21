#include "scheduler.h"
#include "../globals.h"
#include "../config.h"
#include <stdio.h>

void scheduler_init(){
    running = NULL;
}

void* scheduler_thread(void* arg){
    (void) arg;

    while(1){
        sem_wait(&sem_scheduler);

        #if DEBUG
            printf("[SCHEDULER] Tick recebido\n");
        #endif

        if(running == NULL){
            sem_wait(&sem_ready);
            pthread_mutex_lock(&mutex_ready);

            if(!Queue_isEmpty(ready)){
                PCB* aux = (PCB*) Front_queue(ready);
                Remove_queue(ready);

                running = aux;
                PCB_setEstado(aux, RUNNING);

                #if DEBUG
                    printf("[SCHEDULER] PID %d -> RUNNING\n", PCB_getId(aux));
                #endif

                sem_post(&sem_cpu);
            }
            pthread_mutex_unlock(&mutex_ready);
        }
    }

return NULL;
}

void scheduler_addReady(PCB * process){
    if(!process)
        return;

    PCB_setEstado(process, READY);

    pthread_mutex_lock(&mutex_ready);
    Add_queue(ready, process);
    pthread_mutex_unlock(&mutex_ready);

    #if DEBUG
        printf("[SCHEDULER] PID %d -> READY\n", PCB_getId(process));
    #endif

    sem_post(&sem_ready);
}

PCB* scheduler_getRunning(){
    return running;
}

void scheduler_exitCPU(PCB* process){
    if(!process)
        return;

    running = NULL;

    STATE estado = PCB_getEstado(process);

    if(estado == TERMINATED){

        #if DEBUG 
            printf("[SCHEDULER] PID %d TERMINATED\n", PCB_getId(process));
        #endif

        active_process--;

    }else if(estado == BLOCKED){

        pthread_mutex_lock(&mutex_blocked);
        Add_queue(blocked, process);
        pthread_mutex_unlock(&mutex_blocked);

        sem_post(&io_sem);
        
        #if DEBUG 
            printf("[SCHEDULER] PID %d BLOCKED\n", PCB_getId(process));
        #endif       

    }else if(estado == READY){
        scheduler_addReady(process);
    }
}