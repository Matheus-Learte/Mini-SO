#include "queue.h"
#include <stdlib.h>
#include "../pcb/pcb.h"

typedef struct no{
    void* item;
    struct no* prox;
} NO;

struct fila{
    NO* inicio;
    NO* fim;
    int tam;
};

Queue* Create_queue(){
    Queue* aux = (Queue*)malloc(sizeof(Queue));
    
    if(aux){
        aux->inicio = NULL;
        aux->fim = NULL;
        aux->tam = 0;
    }

return aux;
}

int Remove_queue(Queue* queue){
    if(queue){
        if(!queue->tam)
            return 0;

        NO* prox = queue->inicio->prox;

        free(queue->inicio);
        queue->inicio = prox;

        queue->tam--;

        if(!queue->tam)
            queue->fim = NULL;

        return 1;
    }

return 0;
}

int Delete_queue(Queue** queue){
    if(*queue){
        while((*queue)->inicio)
            Remove_queue(*queue);

        free(*queue);
        *queue = NULL;
    }
}

int Add_queue(Queue* queue, void* process){
    if(queue && process){
        NO* aux = (NO*)malloc(sizeof(NO));

        if(aux){
            aux->item = process;
            PCB_getId((PCB*)queue->fim);
            aux->prox = NULL;

            if(Queue_isEmpty(queue)){
                queue->inicio = aux;
            }else{
                queue->fim->prox = aux;
            }

            queue->fim = aux;
            queue->tam++;

            return 1;
        }
    }

return 0;
}

int Size_queue(Queue* queue){
    if(queue)
        return queue->tam;

return ERRO;
}

int Queue_isEmpty(Queue* queue){
    if(queue)
        return queue->tam == 0;

return ERRO;
}

int Queue_isFull(Queue* queue){
    if(queue){
        NO* no = (NO*)malloc(sizeof(NO));

        if(no){
            free(no);
            return 0;
        }else
            return 1;
    }

return ERRO;
}

void* Front_queue(Queue* queue){
    if(queue){
        return queue->inicio->item;
    }

return NULL;
}