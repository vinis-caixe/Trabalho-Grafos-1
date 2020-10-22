#include <stdio.h>
#include <stdlib.h>

struct node{
    int id_professor;
    int livre;
    struct node *prox;
};
typedef struct node LISTA;

LISTA** CriaIniciaLISTA();

int ExisteLISTA(LISTA **inicio);

int ehVaziaLISTA(LISTA **inicio);

int InsereInicioLISTA(LISTA **inicio, int id, int livre);

int InsereFinalLISTA(LISTA **inicio, int id, int livre);

int PosicaoLISTA(LISTA **inicio, int posicao);

int BuscaLISTA(LISTA **inicio, int elemento);

int RemoveInicioLISTA(LISTA **inicio);

int RemoveFinalLISTA(LISTA **inicio);

void ImprimeLISTA(LISTA **inicio);

void LimpaLISTA(LISTA **inicio);

void LiberaLISTA(LISTA **inicio);