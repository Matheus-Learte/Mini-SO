#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "config.h"
#include "globals.h"
#include "queue/queue.h"
#include "pcb/pcb.h"
#include "scheduler/scheduler.h"
#include "clock/clock.h"
#include "cpu/cpu.h"
#include "io/io.h"


Queue* ready = NULL;
Queue* blocked = NULL;

PCB *running = NULL;

int active_process = 0;

sem_t sem_scheduler;
sem_t sem_ready;
sem_t sem_cpu;
sem_t io_sem;
pthread_mutex_t mutex_ready;
pthread_mutex_t mutex_blocked;

int main(){
    pthread_t scheduler, cpu, clock, io;
    
    srand(time(NULL));

    printf("Iniciando mini SO...\n");

    ready = Create_queue();
    blocked = Create_queue();

    scheduler_init();

    if(!ready || !blocked){
        printf("ERRO NA ALOCAÇÃO");
        exit(EXIT_FAILURE);
    }

    scheduler_addReady(Create_process(rand()%300, ((rand()%400)+100), 0));
    scheduler_addReady(Create_process(rand()%300, ((rand()%400)+100), 1));
    scheduler_addReady(Create_process(rand()%300, ((rand()%400)+100), 2));
    scheduler_addReady(Create_process(rand()%300, ((rand()%400)+100), 3));
    scheduler_addReady(Create_process(rand()%300, ((rand()%400)+100), 4));

    pthread_mutex_init(&mutex_ready, NULL);
    pthread_mutex_init(&mutex_blocked, NULL);

    sem_init(&sem_scheduler, 0, 0);
    sem_init(&sem_ready, 0, 5);
    sem_init(&sem_cpu, 0, 0);
    io_init();

    pthread_create(&clock, NULL, clock_thread, NULL);
    pthread_create(&scheduler, NULL, scheduler_thread, NULL);
    pthread_create(&cpu, NULL, cpu_thread, NULL);
    pthread_create(&io, NULL, io_thread, NULL);


    pthread_join(clock, NULL);
    pthread_join(cpu, NULL);
    pthread_join(scheduler, NULL);


    Delete_queue(&ready);
    Delete_queue(&blocked);

    sem_destroy(&sem_scheduler);
    sem_destroy(&sem_ready);
    sem_destroy(&sem_cpu);

    pthread_mutex_destroy(&mutex_ready);
    pthread_mutex_destroy(&mutex_blocked);

    printf("Sistema Finalizado. \n");

return 0;
}