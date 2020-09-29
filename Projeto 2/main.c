#include <stdio.h>
#include <stdlib.h>

typedef struct Struct_Celula *Apontador;
struct Struct_Celula {
    int Codigo;
    int Peso;
    Apontador Prox;
};
typedef struct Struct_Celula Celula;

typedef struct TipoLista {
    Apontador Primeiro, Ultimo;
} TipoLista;

typedef struct TipoGrafo {
    TipoLista Adj[33];      // modificar se for diferente o numero de disciplinas
    int NumVertices;
    int NumArestas;
} TipoGrafo;

void le_arquivo() {
    FILE *arq;
    arq = fopen("disciplinas.txt", "r");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fclose(arq);
}


void cria_lista_vazia(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

void cria_grafo_vazio(TipoGrafo *Grafo) {
    for(int i = 0; i < Grafo->NumVertices; i++)
        cria_lista_vazia(&Grafo->Adj[i]);
}

void libera_grafo(TipoGrafo *Grafo) {
    Apontador anterior, aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        free(Grafo->Adj[i].Primeiro);
        Grafo->Adj[i].Primeiro = NULL;
        while(aux != NULL) {
            anterior = aux;
            aux = aux->Prox;
            free(anterior);
        }
    }
}



int main() {
    le_arquivo();

    TipoGrafo Grafo;
    Grafo.NumVertices = 33; // modificar se for diferente de 33
    Grafo.NumArestas = 123; // depende do número de pre-requisitos (mudar quando souber)

    cria_grafo_vazio(&Grafo);

    libera_grafo(&Grafo);

    return 0;
}