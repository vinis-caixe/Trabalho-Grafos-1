#include <stdio.h>
#include <stdlib.h>

struct node{
    int elem; // Id da matéria
    int cod;  // Código da matéria
    struct node *prox;
};
typedef struct node LISTA;

LISTA** CriaIniciaLISTA();

int ExisteLISTA(LISTA **inicio);

int ehVaziaLISTA(LISTA **inicio);

int InsereFinalLISTA(LISTA **inicio, int novo, int codigo);

int BuscaCodigo(LISTA **inicio, int elemento);

int ExisteElemento(LISTA **inicio, int elemento);

void ImprimeLISTA(LISTA **inicio);

void LimpaLISTA(LISTA **inicio);

void LiberaLISTA(LISTA **inicio);
