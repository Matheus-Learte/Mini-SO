#ifndef __QUEUE__
    #define __QUEUE__

        #define ERRO -32000
        
        typedef struct fila Queue;

        Queue* Create_queue();
        int Add_queue(Queue* queue, void* process);
        int Remove_queue(Queue* queue);
        int Delete_queue(Queue** queue);

        void* Front_queue(Queue* queue);
        int Size_queue(Queue* queue);
        int Queue_isEmpty(Queue* queue);
        int Queue_isFull(Queue* queue);

#endif