#include "lista.h"

// Função que cria uma nova lista
LISTA ** CriaIniciaLISTA(){
	LISTA **novo;

	novo = (LISTA **) malloc(sizeof(LISTA *));

	*novo = NULL;

	return novo;
}

// Verifica se exite uma lista existe
int ExisteLISTA(LISTA **inicio){
	if(inicio == NULL)
		return 0;

	return 1;
}

// Verifica se a lista é vazia
int ehVaziaLISTA(LISTA **inicio){
	if(*inicio == NULL)
		return 1;

	return 0;
}

// Insere um novo elemento no final da lista junto com seu código
int InsereFinalLISTA(LISTA **inicio, int novo, int codigo, int adjacente){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	LISTA *aux, *ant, *novono;

	novono = (LISTA *) malloc(sizeof(LISTA));
	if(novono == NULL)
		return 0;

	novono->cod = codigo;
	novono->elem = novo;
	novono->id_adjacente = adjacente;
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

// Procura um Id na lista e retorna seu código
int BuscaCodigo(LISTA **inicio, int elemento){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	LISTA *aux;

	aux = *inicio;

	while(aux != NULL){
		if(aux->elem == elemento)
			return aux->cod;

		aux = aux->prox;
	}

	return 0;
}

// Verifica se um Id está na lista
int ExisteElemento(LISTA **inicio, int elemento, int adjacente){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	LISTA *aux;

	aux = *inicio;

	while(aux != NULL){
		if(aux->elem == elemento && aux->id_adjacente == adjacente)
			return 1;

		if(aux->elem == elemento && adjacente == -1)
			return 1;

		aux = aux->prox;
	}

	return 0;
}

// Imprime a lista
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
		printf("%d %d %d => ", aux->elem, aux->cod, aux->id_adjacente);
		aux = aux->prox;
	}

	printf("\n");
}

// Remove todos os elementos da lista
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

// Remove os elementos da lista e libera a lista
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
