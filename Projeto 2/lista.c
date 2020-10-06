#include "lista.h"

LISTA ** CriaIniciaLISTA(){
	LISTA **novo;

	novo = (LISTA **) malloc(sizeof(LISTA *));

	*novo = NULL;

	return novo;
}

int ExisteLISTA(LISTA **inicio){
	if(inicio == NULL)
		return 0;

	return 1;
}

int ehVaziaLISTA(LISTA **inicio){
	if(*inicio == NULL)
		return 1;

	return 0;
}

int InsereInicioLISTA(LISTA **inicio, int novo){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	LISTA *novono;

	novono = (LISTA *) malloc(sizeof(LISTA));
	if(novono == NULL)
		return 0;

	novono->prox = NULL;
	novono->elem = novo;

	LISTA *aux;

	aux = *inicio;

	*inicio = novono;

	novono->prox = aux;

	return 1;
}

int InsereFinalLISTA(LISTA **inicio, int novo){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	LISTA *aux, *ant, *novono;

	novono = (LISTA *) malloc(sizeof(LISTA));
	if(novono == NULL)
		return 0;

	novono->elem = novo;
	novono->prox = NULL;

	if(ehVaziaLISTA(inicio) == 1){
		*inicio = novono;
		return 1;
	}

	aux = *inicio;

	while(aux != NULL){
		ant = aux;

		aux = aux->prox;
	}

	ant->prox = novono;

	return 1;
}

int PosicaoLISTA(LISTA **inicio, int posicao){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	int atual = 0;

	LISTA *aux;

	aux = *inicio;

	while(aux != NULL){
		if(atual == posicao)
			return aux->elem;

		atual++;
		aux = aux->prox;
	}

	return 0;
}

int BuscaLISTA(LISTA **inicio, int elemento){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	int i = 1;

	LISTA *aux;

	aux = *inicio;

	while(aux != NULL){
		if(aux->elem == elemento)
			return i;

		i++;

		aux = aux->prox;
	}

	return 0;
}

int RemoveInicioLISTA(LISTA **inicio){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	LISTA *aux;

	aux = *inicio;

	*inicio = (*inicio)->prox;

	free(aux);

	return 1;
}

int RemoveFinalLISTA(LISTA **inicio){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	LISTA *aux, *ant;

	aux = *inicio;

	if(aux->prox == NULL){
		free(aux);
		*inicio = NULL;
		return 1;
	}

	while(aux->prox != NULL){
		ant = aux;

		aux = aux->prox;
	}

	free(aux);

	ant->prox = NULL;

	return 1;
}

void ImprimeLISTA(LISTA **inicio){
	if(ExisteLISTA(inicio) == 0){
		printf("Erro! Lista nao existe.");
		return;
	}

	if(ehVaziaLISTA(inicio) == 1){
		printf("Lista vazia.");
		return;
	}

	LISTA *aux;

	aux = *inicio;

	while(aux != NULL){
		printf("%d => ", aux->elem);
		aux = aux->prox;
	}

	printf("\n");
}

void LimpaLISTA(LISTA **inicio){
	if(ehVaziaLISTA(inicio) == 1)
		return;

	if(ExisteLISTA(inicio) == 0)
		return;

	LISTA *aux, *ant;

	aux = *inicio;

	while(aux != NULL){
		ant = aux;

		aux = aux->prox;

		free(ant);
	}

	*inicio = NULL;
}

void LiberaLISTA(LISTA **inicio){

	if(ExisteLISTA(inicio) == 0)
		return;

	LISTA *aux, *ant;

	aux = *inicio;

	while(aux != NULL){
		ant = aux;

		aux = aux->prox;

		free(ant);
	}

	free(inicio);

	inicio = NULL;
}
