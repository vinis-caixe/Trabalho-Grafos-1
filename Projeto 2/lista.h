#include <stdio.h>
#include <stdlib.h>

struct dados{
    int info;
};
typedef struct dados Data;

struct node{
    Data elem;
    struct node *prox;
};
typedef struct node LADAE;

LADAE** CriaIniciaLADAE();

int ExisteLADAE(LADAE **inicio);

int ehVaziaLADAE(LADAE **inicio);

int InsereInicioLADAE(LADAE **inicio, Data novo);

int InsereFinalLADAE(LADAE **inicio, Data novo);

int BuscaLADAE(LADAE **inicio, int elemento);

int RemoveInicioLADAE(LADAE **inicio);

int RemoveFinalLADAE(LADAE **inicio);

void ImprimeLADAE(LADAE **inicio);

void LimpaLADAE(LADAE **inicio);

void LiberaLADAE(LADAE **inicio);
