#ifndef __STATS__
    #define __STATS__

    #include "../pcb/pcb.h"

    typedef struct stats_ Stats;

    void stats_allocation();
    void stats_on_tick();
    void stats_on_running(PCB* p);
    void stats_on_ready(PCB* p);
    void stats_on_exit_ready(PCB* p);
    void stats_on_blocked(PCB* p);
    void stats_on_exit_blocked(PCB* p);
    void stats_on_terminated(PCB* p);
    void stats_print();

#endif