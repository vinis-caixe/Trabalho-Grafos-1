#include <stdio.h>
#include <stdlib.h>

struct node{
    int id_professor;
    int id_escola;
    struct node *prox;
};
typedef struct node LISTA;

LISTA** CriaIniciaLISTA();

int ExisteLISTA(LISTA **inicio);

int ehVaziaLISTA(LISTA **inicio);

int InsereInicioLISTA(LISTA **inicio, int professor, int escola);

int InsereFinalLISTA(LISTA **inicio, int professor, int escola);

int ProfessorLISTA(LISTA **inicio, int escola, int habilitacao);

int TrocaProfessorLISTA(LISTA **inicio, int escola, int atual, int substituto);

int BuscaLISTA(LISTA **inicio, int elemento);

int RemoveInicioLISTA(LISTA **inicio);

int RemoveFinalLISTA(LISTA **inicio);

void ImprimeLISTA(LISTA **inicio);

void LimpaLISTA(LISTA **inicio);

void LiberaLISTA(LISTA **inicio);