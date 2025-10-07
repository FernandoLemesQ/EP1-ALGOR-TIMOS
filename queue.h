#ifndef _QUEUE_
#define _QUEUE_

#include "list.h"

typedef struct Queue {
    
    struct CELULA *comeco; 

    struct CELULA *fim;
} Queue;

Queue*  create_queue();
void    enqueue(Queue *Q, int novo_valor);
int     dequeue(Queue *Q);
int     front(Queue *Q);
int     queue_is_empty(Queue *Q);

#endif