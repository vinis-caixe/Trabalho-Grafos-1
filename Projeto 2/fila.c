#include "fila.h"

FILA** criaFILA() {
    FILA **novo;

    novo = (FILA **) malloc(sizeof(FILA *));

    *novo = NULL;

    return novo;
}

FILA_CRITICO** criaFILA_CRITICO() {
    FILA_CRITICO **novo;

    novo = (FILA_CRITICO **) malloc(sizeof(FILA_CRITICO *));

    *novo = NULL;

    return novo;
}

int ehVaziaFILA(FILA **inicio) {

    if(*inicio == NULL) {
        return 1;
    }

    return 0;
}

int ehVaziaFILA_CRITICO(FILA_CRITICO **inicio) {

    if(*inicio == NULL) {
        return 1;
    }

    return 0;
}

// Coloca um novo nó no final da fila
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

int enfileirar_CRITICO(FILA_CRITICO **inicio, int novo) {
    FILA_CRITICO *novono, *aux, *ant;
    aux = *inicio;
    ant = aux;


    novono = (FILA *) malloc(sizeof(FILA));
    if(novono == NULL)
        return 0;

    novono->prox = NULL;
    novono->vertice_crtitico = novo;

    if(ehVaziaFILA_CRITICO(inicio) == 1) {
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

// Retira o primeiro nó da fila
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

int desenfileirar_CRITICO(FILA_CRITICO **inicio) {
    if(ehVaziaFILA_CRITICO(inicio) == 1) {
        return 0;
    }

    FILA_CRITICO *aux, *ant;
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

void liberaFILA_CRITICO(FILA_CRITICO **inicio) {
    while(ehVaziaFILA_CRITICO(inicio) != 1)
    	desenfileirar_CRITICO(inicio);

    free(inicio);
    inicio = NULL;

}

void limparFILA(FILA **inicio) {

    while(ehVaziaFILA(inicio) != 1)
    	desenfileirar(inicio);

}

// Retorna o primeiro nó da fila
TipoLista primeiroFILA(FILA **primeiro) {

    FILA *auxi;

    auxi = *primeiro;

    TipoLista res;

    res = auxi->vertice;

    return res;
}
