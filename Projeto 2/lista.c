#include "ladae.h"

LADAE ** CriaIniciaLADAE(){
	LADAE **novo;

	novo = (LADAE **) malloc(sizeof(LADAE *));

	*novo = NULL;

	return novo;
}

int ExisteLADAE(LADAE **inicio){
	if(inicio == NULL)
		return 0;

	return 1;
}

int ehVaziaLADAE(LADAE **inicio){
	if(*inicio == NULL)
		return 1;

	return 0;
}

int InsereInicioLADAE(LADAE **inicio, Data novo){
	if(ExisteLADAE(inicio) == 0)
		return 0;

	LADAE *novono;

	novono = (LADAE *) malloc(sizeof(LADAE));
	if(novono == NULL)
		return 0;

	novono->prox = NULL;
	novono->elem = novo;

	LADAE *aux;

	aux = *inicio;

	*inicio = novono;

	novono->prox = aux;

	return 1;
}

int InsereFinalLADAE(LADAE **inicio, Data novo){
	if(ExisteLADAE(inicio) == 0)
		return 0;

	LADAE *aux, *ant, *novono;

	novono = (LADAE *) malloc(sizeof(LADAE));
	if(novono == NULL)
		return 0;

	novono->elem = novo;
	novono->prox = NULL;

	if(ehVaziaLADAE(inicio) == 1)
		*inicio = novono;

	aux = *inicio;

	while(aux != NULL){
		ant = aux;

		aux = aux->prox;
	}

	ant->prox = novono;

	return 1;
}

int BuscaLADAE(LADAE **inicio, int elemento){
	if(ExisteLADAE(inicio) == 0)
		return 0;

	if(ehVaziaLADAE(inicio) == 1)
		return 0;

	int i = 1;

	LADAE *aux;

	aux = *inicio;

	while(aux != NULL){
		if(aux->elem.info == elemento)
			return i;

		i++;

		aux = aux->prox;
	}

	return 0;
}

int RemoveInicioLADAE(LADAE **inicio){
	if(ExisteLADAE(inicio) == 0)
		return 0;

	if(ehVaziaLADAE(inicio) == 1)
		return 0;

	LADAE *aux;

	aux = *inicio;

	*inicio = (*inicio)->prox;

	free(aux);

	return 1;
}

int RemoveFinalLADAE(LADAE **inicio){
	if(ExisteLADAE(inicio) == 0)
		return 0;

	if(ehVaziaLADAE(inicio) == 1)
		return 0;

	LADAE *aux, *ant;

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

void ImprimeLADAE(LADAE **inicio){
	if(ExisteLADAE(inicio) == 0){
		printf("Erro! Lista nao existe.");
		return;
	}

	if(ehVaziaLADAE(inicio) == 1){
		printf("Lista vazia.");
		return;
	}

	LADAE *aux;

	aux = *inicio;

	while(aux != NULL){
		printf("%d => ", aux->elem.info);
		aux = aux->prox;
	}

	printf("\n");
}

void LimpaLADAE(LADAE **inicio){
	if(ehVaziaLADAE(inicio) == 1)
		return;

	if(ExisteLADAE(inicio) == 0)
		return;

	LADAE *aux, *ant;

	aux = *inicio;

	while(aux != NULL){
		ant = aux;

		aux = aux->prox;

		free(ant);
	}

	*inicio = NULL;
}

void LiberaLADAE(LADAE **inicio){

	if(ExisteLADAE(inicio) == 0)
		return;

	LADAE *aux, *ant;

	aux = *inicio;

	while(aux != NULL){
		ant = aux;

		aux = aux->prox;

		free(ant);
	}

	free(inicio);

	inicio = NULL;
}
