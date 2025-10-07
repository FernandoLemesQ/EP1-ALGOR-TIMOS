#include <stdio.h>
#include <stdlib.h>
#include "list.h"

CELULA* list_empty(){
    return NULL;
}

CELULA *cria_list (int v[], int n){
    CELULA *lst;
    lst = NULL;
    int i = n - 1;
    while (i >= 0) {
        lst = insere_cel(lst, v[i]);
        i--;
    }
    return lst;
}

CELULA* busca_list(CELULA *lst, int y){
    if (lst == NULL)                     
       return NULL;
    if (lst->conteudo == y)                 
       return lst;
    return busca_list(lst->prox, y); 
}

void print_list (CELULA *lst) { 
   CELULA *p;    
   for (p = lst; p!= NULL; p = p->prox)
       printf("%d\n", p->conteudo);
}
CELULA *insere_cel (CELULA *lst, int y){
      CELULA *nova_celula = malloc(sizeof(CELULA));
      nova_celula->conteudo = y;
      nova_celula->prox = lst;
      return nova_celula;
  }

void remove_cel(CELULA **lst, CELULA *p){ 
     if (*lst == NULL || p == NULL) 
     return; 
     if (*lst == p) {   
       *lst = p->prox;   
             free(p);        
    return;    
}   
    CELULA *aux;    
        aux = *lst;
    while (aux->prox != NULL && aux->prox != p) {
        aux = aux->prox;
    }

    if (aux->prox == p) {
        aux->prox = p->prox;
        free(p);
    }    
}