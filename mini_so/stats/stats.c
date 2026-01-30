#include <stdio.h>
#include <stdlib.h>
#include "stats.h"
#include "../globals.h"
#include "../Lista/lista.h"

struct stats_{
    int cpu_time;
    int waiting_time;
    int io_time;
    int finish_time;
    int arrival_time;
    int ready_start_time;
    int blocked_start_time;
    int first_ready;
    int valid;
};

static LISTA* lista;
static int stats_count = 0;

void stats_allocation(){
    lista = lista_criar();
    
    Stats* s0 = (Stats*) calloc(1, sizeof(Stats));
    Stats* s1 = (Stats*) calloc(1, sizeof(Stats));
    Stats* s2 = (Stats*) calloc(1, sizeof(Stats));
    Stats* s3 = (Stats*) calloc(1, sizeof(Stats));
    Stats* s4 = (Stats*) calloc(1, sizeof(Stats));
    
    // Inicializar tempos como -1 para evitar cálculos incorretos
    s0->ready_start_time = s0->blocked_start_time = -1;
    s1->ready_start_time = s1->blocked_start_time = -1;
    s2->ready_start_time = s2->blocked_start_time = -1;
    s3->ready_start_time = s3->blocked_start_time = -1;
    s4->ready_start_time = s4->blocked_start_time = -1;
    
    lista_inserir(lista, s0, 0);
    lista_inserir(lista, s1, 1);
    lista_inserir(lista, s2, 2);
    lista_inserir(lista, s3, 3);
    lista_inserir(lista, s4, 4);

    stats_count=5;
}

void stats_on_tick(){
    global_time++;
}

void stats_on_running(PCB *p){
    int id = PCB_getId(p);

    ((Stats*)lista_buscar(lista, id))->cpu_time++;
}

void stats_on_ready(PCB *p){
    int id = PCB_getId(p);
    Stats* stats = (Stats*)lista_buscar(lista, id);
    
    if(!stats->first_ready){
        stats->arrival_time = 0;  // Todos os processos chegam no tempo 0
        stats->first_ready = 1;
    }
    
    stats->ready_start_time = global_time;
}

void stats_on_blocked(PCB *p){
    int id = PCB_getId(p);

    ((Stats*)lista_buscar(lista, id))->blocked_start_time = global_time;
}

void stats_on_exit_ready(PCB *p){
    int id = PCB_getId(p);
    Stats* stats = (Stats*)lista_buscar(lista, id);
    
    if(stats->ready_start_time >= 0){
        stats->waiting_time += global_time - stats->ready_start_time;
        stats->ready_start_time = -1; // Reset para evitar dupla contagem
    }
}

void stats_on_exit_blocked(PCB *p){
    int id = PCB_getId(p);
    Stats* stats = (Stats*)lista_buscar(lista, id);
    
    if(stats->blocked_start_time >= 0){
        stats->io_time += global_time - stats->blocked_start_time;
        stats->blocked_start_time = -1; // Reset para evitar dupla contagem
    }
}

void stats_on_terminated(PCB *p) {
    int id = PCB_getId(p);
    
    ((Stats*)lista_buscar(lista, id))->finish_time = global_time;
    ((Stats*)lista_buscar(lista, id))->valid = 1;
}

void stats_print(void) {
    printf("\n===== ESTATISTICAS =====\n");
    printf("PID | CPU | WAIT | IO | TURNAROUND\n");
    printf("----------------------------------\n");

    for (int i = 0; i < stats_count; i++) {
        if (!((Stats*)lista_buscar(lista, i))->valid) continue;

        Stats* s = (Stats*)lista_buscar(lista, i);
        int turnaround = s->cpu_time + s->waiting_time + s->io_time;

        printf("%3d | %3d | %4d | %2d | %4d\n",
               i, s->cpu_time, s->waiting_time, s->io_time, turnaround);
    }
}