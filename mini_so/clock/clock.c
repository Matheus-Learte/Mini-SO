#include "clock.h"
#include "../globals.h"
#include "../config.h"
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

void* clock_thread(void* arg){
    (void) arg;

    while(1){
        usleep(TICK_MS*1000);

        sem_post(&sem_scheduler);

        #if DEBUG
            printf("[CLOCK] TIck!\n");
        #endif
    }

return NULL;
}