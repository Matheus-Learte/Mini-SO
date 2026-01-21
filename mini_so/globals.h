#ifndef __GLOBAL__
    #define __GLOBAL__

    #include <pthread.h>
    #include <semaphore.h>

    #include "pcb/pcb.h"
    #include "queue/queue.h"

    // =========== FILAS =============
    extern Queue* ready;
    extern Queue* blocked;

    // ============ PROCESSO EM EXECUÇÂO ==============
    extern PCB *running;

    // ============= CONTADOR GLOBAL ================
    extern int active_process;

    // ============== SEMAFOROS =====================
    extern sem_t sem_scheduler;
    extern sem_t sem_ready;
    extern sem_t sem_cpu;
    extern sem_t io_sem;

    // =============== MUTEXES ===================
    extern pthread_mutex_t mutex_ready;
    extern pthread_mutex_t mutex_blocked;

#endif