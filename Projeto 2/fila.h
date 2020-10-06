#include <stdio.h>
#include <stdlib.h>

typedef struct Struct_Celula *Apontador;
struct Struct_Celula {
    int Id;
    char Codigo[7];
    int Peso;
    Apontador Prox;
};
typedef struct Struct_Celula Celula;

typedef struct TipoLista {
    Apontador Primeiro, Ultimo;
    char Codigo_Vertice[7];
    int Peso_Vertice;
    int Id_Vertice;
} TipoLista;

typedef struct TipoGrafo {
    TipoLista Adj[33];
    int NumVertices;
    int NumArestas;
} TipoGrafo;

typedef struct fila {
    TipoLista vertice;
    struct fila *prox;
} FILA;

typedef struct fila_critico {
    int vertice_crtitico;
    struct fila *prox;
} FILA_CRITICO;

FILA** criaFILA();

int ehVaziaFILA(FILA **inicio);

int enfileirar(FILA **inicio, TipoLista novo);

int desenfileirar(FILA **inicio);

TipoLista primeiroFILA(FILA **inicio);

void limparFILA(FILA **inicio);

void liberaFILA(FILA **inicio);