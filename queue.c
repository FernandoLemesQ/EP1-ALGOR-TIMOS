#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "queue.h"


void enqueue(Queue* Q, int novo_valor){
    CELULA *nova = malloc (sizeof (CELULA));
    nova->conteudo = novo_valor;
    nova->prox = NULL;
    if (Q -> fim == NULL){ 
        Q -> comeco = Q->fim = nova; 
    } else {
        Q -> fim->prox = nova; 
        Q -> fim = nova; 
    }
}

int dequeue(Queue* Q){
    if (Q->comeco == NULL) { 
        return -1;
    }

    CELULA* p = Q -> comeco; 
    int x = p -> conteudo;
    Q->comeco = p -> prox; 
    if ( Q-> comeco == NULL){
            Q -> fim = NULL; 
    }

    free(p); 
    return x; 
}

int queue_is_empty(Queue* Q){
    if (Q->comeco == NULL){
        return 1; 
    } else {
        return 0; 
    }
}
Queue* create_queue(){
    Queue* Q = malloc (sizeof (Queue)); 
    Q-> comeco = NULL; 
    Q-> fim = NULL; 
    return Q;
}

int front(Queue* Q){
   if (Q->comeco == NULL) { 
        return -1;
    }
    return Q->comeco->conteudo;
}