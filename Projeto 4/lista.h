#include <stdio.h>
#include <stdlib.h>

struct node{
    int elem; // Horário
    int cod;  // Código da matéria
    int id_adjacente; // Id do adjacente ao vértice colorido
    struct node *prox;
};
typedef struct node LISTA;

LISTA** CriaIniciaLISTA();

int ExisteLISTA(LISTA **inicio);

int ehVaziaLISTA(LISTA **inicio);

int InsereFinalLISTA(LISTA **inicio, int novo, int codigo, int adjacente);

int BuscaCodigo(LISTA **inicio, int elemento);

int ExisteElemento(LISTA **inicio, int elemento, int adjacente);

void ImprimeLISTA(LISTA **inicio);

void LimpaLISTA(LISTA **inicio);

void LiberaLISTA(LISTA **inicio);
