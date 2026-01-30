#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdatomic.h>

#include "config.h"
#include "globals.h"
#include "queue/queue.h"
#include "pcb/pcb.h"
#include "scheduler/scheduler.h"
#include "clock/clock.h"
#include "cpu/cpu.h"
#include "io/io.h"
#include "stats/stats.h"


Queue* ready = NULL;
Queue* blocked = NULL;

PCB *running = NULL;

int active_process = 0;
int global_time = 0;
atomic_int system_running = 1;

sem_t sem_scheduler;
sem_t sem_cpu;
sem_t io_sem;

pthread_mutex_t mutex_ready;
pthread_mutex_t mutex_blocked;
pthread_mutex_t mutex_global_time;

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

    scheduler_addReady(Create_process(0, (rand()%100), 0));
    scheduler_addReady(Create_process(1, (rand()%100), 0));
    scheduler_addReady(Create_process(2, (rand()%100), 0));
    scheduler_addReady(Create_process(3, (rand()%100), 0));
    scheduler_addReady(Create_process(4, (rand()%100), 0));

    active_process = 5;

    stats_allocation();

    pthread_mutex_init(&mutex_ready, NULL);
    pthread_mutex_init(&mutex_blocked, NULL);
    pthread_mutex_init(&mutex_global_time, NULL);

    sem_init(&sem_scheduler, 0, 0);
    sem_init(&sem_cpu, 0, 0);
    io_init();

    pthread_create(&clock, NULL, clock_thread, NULL);
    pthread_create(&scheduler, NULL, scheduler_thread, NULL);
    pthread_create(&cpu, NULL, cpu_thread, NULL);
    pthread_create(&io, NULL, io_thread, NULL);


    pthread_join(clock, NULL);
    pthread_join(cpu, NULL);
    pthread_join(scheduler, NULL);
    pthread_join(io, NULL);

    stats_print();


    Delete_queue(&ready);
    Delete_queue(&blocked);

    sem_destroy(&sem_scheduler);
    sem_destroy(&sem_cpu);

    pthread_mutex_destroy(&mutex_ready);
    pthread_mutex_destroy(&mutex_blocked);
    pthread_mutex_destroy(&mutex_global_time);

    printf("Sistema Finalizado. \n");

return 0;
}