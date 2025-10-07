#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "stack.h"

Stack* create_stack(){
    Stack* s = (Stack*)  malloc (sizeof (Stack)); 
    s->t = NULL; 
    return s; 
}

void push(Stack* s, int novo_valor){
    CELULA *nova_celula = malloc(sizeof(CELULA));
      nova_celula->conteudo = novo_valor;
      nova_celula->prox = s -> t ;
      s->t = nova_celula;
}

int pop(Stack* s){
    if (s->t == NULL) return -1;

    CELULA* p = s->t; 
    int x = p -> conteudo; 
    s->t = p -> prox; 

    free(p); 
    return x; 
}

int top(Stack* s){
    if (s->t == NULL) return -1;
    return s->t->conteudo;  
}

int stack_is_empty(Stack* s){
    if (s->t == NULL) return 1;
    else return 0; 
    
}
