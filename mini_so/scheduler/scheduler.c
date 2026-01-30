#include "scheduler.h"
#include "../globals.h"
#include "../config.h"
#include "../stats/stats.h"
#include <stdio.h>

void scheduler_init(){
    running = NULL;
}

void* scheduler_thread(void* arg){
    (void) arg;

    while(atomic_load(&system_running)){
        sem_wait(&sem_scheduler);

        if(!atomic_load(&system_running)) break;

        #if DEBUG
            printf("[SCHEDULER] Tick recebido\n");
        #endif

        if(running == NULL){
            pthread_mutex_lock(&mutex_ready);

            if(!Queue_isEmpty(ready)){
                PCB* aux = (PCB*) Front_queue(ready);
                Remove_queue(ready);

                running = aux;
                PCB_setEstado(aux, RUNNING);
                stats_on_exit_ready(aux);

                #if DEBUG
                    printf("[SCHEDULER] PID %d -> RUNNING\n", PCB_getId(aux));
                #endif
            } else {
                #if DEBUG
                    printf("[SCHEDULER] Nenhum processo pronto\n");
                #endif
            }
            pthread_mutex_unlock(&mutex_ready);
        }
        
        sem_post(&sem_cpu);
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
        stats_on_terminated(process);

        if(active_process == 0){
            atomic_store(&system_running, 0);
            sem_post(&sem_cpu);
            sem_post(&sem_scheduler);
            sem_post(&io_sem);
        }

    }else if(estado == BLOCKED){
        pthread_mutex_lock(&mutex_blocked);
        Add_queue(blocked, process);
        pthread_mutex_unlock(&mutex_blocked);

        stats_on_blocked(process);

        sem_post(&io_sem);
        
        #if DEBUG 
            printf("[SCHEDULER] PID %d BLOCKED\n", PCB_getId(process));
        #endif       

    }else if(estado == READY){
        stats_on_ready(process);
        scheduler_addReady(process);
    }
}