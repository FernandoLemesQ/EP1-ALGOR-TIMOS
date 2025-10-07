#include <stdio.h>
#include <stdlib.h>

#include "list.h"
#include "graph.h"

Graph* create_graph(int n, int type) {   
    // aloca o grafo
    Graph* G = malloc(sizeof(Graph));  
    if (G == NULL) 
        return NULL;

    G->n = n;   
    G->type = type;  
    G->mat_adj = NULL;   
    G->list_adj = NULL;
   
    // lista de adjacência
    if (type == 0) {         
        G->list_adj = malloc(n * sizeof(CELULA*));             
        int i = 0;
        while (i < n) {
            G->list_adj[i] = list_empty();
            i++;
        }
    }else if (type == 1) {         
        // matriz de adjacência
        G->mat_adj = malloc(n * sizeof(int*));                
        int i = 0;
        while (i < n) {            
            G->mat_adj[i] = malloc(n * sizeof(int));            
            int j = 0;
            // inicializa tudo com 0
            while (j < n) {
                G->mat_adj[i][j] = 0;
                j++;
            }
            i++;
        }    
    }
    else{
        printf("Tipagem do grafo nao identificada"); //aviso caso o usuario entre com uma tipagem incorreta
    }
    return G;
}

int add_edge(Graph *G, int u, int v) {        
    // lista de adjacência
    if (G->type == 0) {    
        // verifica se a aresta já existe
        if (busca_list(G->list_adj[u], v) == NULL) {
            insere_cel(G->list_adj[u], v);
            insere_cel(G->list_adj[v], u);  // grafo não direcionado
            return 1;  
        }
        return 0;
    } else {
        // matriz de adjacência
        if (G->mat_adj[u][v] == 0) {
            G->mat_adj[u][v] = 1;
            G->mat_adj[v][u] = 1;  
            return 1;  
        }
        return 0; 
    }
}

int remove_edge(Graph *G, int u, int v){    
    if (G->type == 0) {    
        // verifica se a aresta existe
        if (busca_list(G->list_adj[u], v) == NULL)
            return 0;
        remove_cel(&G->list_adj[u], busca_list(G->list_adj[u], v));
        remove_cel(&G->list_adj[v], busca_list(G->list_adj[v], u));
        return 1;  
    } else {
        if (G->mat_adj[u][v] == 1) {
            G->mat_adj[u][v] = 0;
            G->mat_adj[v][u] = 0;  
            return 1;  
        }
        return 0; 
    }
}

int* bfs(Graph *G, int u){
    int n = G->n;
    int *d = malloc(n * sizeof(int));

    // inicializa distâncias como -1 (não visitado)
    int v = 0;
    while (v < n) {
        d[v] = -1;
        v++;
    }
    
    d[u] = 0;  // distância do vértice inicial é 0

    Queue *Q = create_queue();
    enqueue(Q, u); 

    while (!queue_is_empty(Q)) {
        u = dequeue(Q); 

        // lista de adjacência
        if (G->type == 0) { 
            CELULA *p = G->list_adj[u];
            while (p != NULL) {
                int v = p->conteudo;
                if (d[v] == -1) {  // ainda não visitado
                    d[v] = d[u] + 1; 
                    enqueue(Q, v); 
                }
                p = p->prox;
            }
        } else { 
            // matriz de adjacência
            v = 0;
            while (v < n) {
                if (G->mat_adj[u][v] == 1 && d[v] == -1) {
                    d[v] = d[u] + 1; 
                    enqueue(Q, v); 
                }
                v++;
            }
        }
    }

    free(Q);

    return d;  // retorna array com as distâncias
}

int* dfs(Graph *G, int u){
    int n = G->n;
    int *p = malloc(n * sizeof(int));   
    
    int v = 0;
    while (v < n) {
        p[v] = -1;
        v++;
    }
    
    Stack *S = create_stack();
    push(S, u); 
    p[u] = u; 

    while (!stack_is_empty(S)) {
        int x = pop(S);  
        
        if (G->type == 0) { 
            CELULA *a = G->list_adj[x];
            while (a != NULL) {
                int v = a->conteudo;
                if (p[v] == -1) { 
                    p[v] = x; 
                    push(S, v); 
                }
                a = a->prox;
            }
        } else {
            v = 0;
            while (v < n) {
                if (G->mat_adj[x][v] == 1 && p[v] == -1) { 
                    p[v] = x; 
                    push(S, v); 
                }
                v++;
            }
        }
    }

    free(S);

    return p;
}

int is_connected(Graph *G){
    if (G == NULL) 
        return 0;

    int *p = dfs(G, 0);  // escolhi dfs pois ocupa menos memória
    if (p == NULL) 
        return 0;

    int v = 0;
    while (v < G->n) {
        if (p[v] == -1) {
            free(p);
            return 0;
        }
        v++;
    }

    free(p);
    return 1; 
}