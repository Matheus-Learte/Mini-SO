#include "clock.h"
#include "../globals.h"
#include "../config.h"
#include "../stats/stats.h"
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>

void* clock_thread(void* arg){
    (void) arg;

    while(atomic_load(&system_running)){
        usleep(TICK_MS*1000);

        stats_on_tick();
        sem_post(&sem_scheduler);

        #if DEBUG
            printf("[CLOCK] TIck!\n");
        #endif
    }

return NULL;
}