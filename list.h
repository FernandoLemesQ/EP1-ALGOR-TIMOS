#ifndef _LIST_H
#define _LIST_H

typedef struct CELULA{
    int conteudo;
    struct CELULA *prox;
  } CELULA;

CELULA* list_empty();
CELULA*  insere_cel(CELULA *lst, int y);
CELULA *cria_list (int v[], int n);
void remove_cel(CELULA **lst, CELULA *p);
CELULA* busca_list(CELULA *lst, int y);
void print_list (CELULA *lst);

#endif