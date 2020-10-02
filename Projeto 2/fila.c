#include "fila.h"

FILA** criaFILA() {
    FILA **novo;

    novo = (FILA **) malloc(sizeof(FILA *));

    *novo = NULL;

    return novo;
}

int ehVaziaFILA(FILA **inicio) {

    if(*inicio == NULL) {
        return 1;
    }

    return 0;
}

int enfileirar(FILA **inicio, TipoLista novo) {
    FILA *novono, *aux, *ant;
    aux = *inicio;
    ant = aux;


    novono = (FILA *) malloc(sizeof(FILA));
    if(novono == NULL)
        return 0;

    novono->prox = NULL;
    novono->vertice = novo;

    if(ehVaziaFILA(inicio) == 1) {
        *inicio = novono;
        return 1;
    }

    while(aux != NULL) {
        ant = aux;
        aux = aux->prox;
    }

    ant->prox = novono;

    return 1;
}

int desenfileirar(FILA **inicio) {
    if(ehVaziaFILA(inicio) == 1) {
        return 0;
    }

    FILA *aux, *ant;
    aux = *inicio;
    ant = aux;

    aux = aux->prox;

    *inicio = aux;

    free(ant);

    ant = NULL;

    return 1;
}

void liberaFILA(FILA **inicio) {
    while(ehVaziaFILA(inicio) != 1)
    	desenfileirar(inicio);

    free(inicio);
    inicio = NULL;

}

void limparFILA(FILA **inicio) {

    while(ehVaziaFILA(inicio) != 1)
    	desenfileirar(inicio);

}

TipoLista primeiroFILA(FILA **primeiro) {

    FILA *auxi;

    auxi = *primeiro;

    TipoLista res;

    res = auxi->vertice;

    return res;
}
