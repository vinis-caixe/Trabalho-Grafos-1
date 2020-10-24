#include "lista.h"

// Função que cria uma nova lista
LISTA ** CriaIniciaLISTA(){
	LISTA **novo;

	novo = (LISTA **) malloc(sizeof(LISTA *));

	*novo = NULL;

	return novo;
}

// Verifica se exite uma lista
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

// Insere um novo elemento no início da lista
int InsereInicioLISTA(LISTA **inicio, int professor, int escola){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	LISTA *novono;

	novono = (LISTA *) malloc(sizeof(LISTA));
	if(novono == NULL)
		return 0;

	novono->prox = NULL;
	novono->id_professor = professor;
    novono->id_escola = escola;

	LISTA *aux;

	aux = *inicio;

	*inicio = novono;

	novono->prox = aux;

	return 1;
}

// Insere um novo elemento no final da lista
int InsereFinalLISTA(LISTA **inicio, int professor, int escola){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	LISTA *aux, *ant, *novono;

	novono = (LISTA *) malloc(sizeof(LISTA));
	if(novono == NULL)
		return 0;

	novono->id_professor = professor;
    novono->id_escola = escola;
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

// Retorna um elemento em determinada posição
int ProfessorLISTA(LISTA **inicio, int escola, int habilitacao){
	if(ExisteLISTA(inicio) == 0)
		return -1;

	if(ehVaziaLISTA(inicio) == 1)
		return -1;

	LISTA *aux;

	aux = *inicio;

	while(aux != NULL){
		if(aux->id_escola == escola && habilitacao == 1){
			return aux->id_professor;
		}

		if(aux->id_escola == escola && habilitacao == 2){
			habilitacao = 1;
		}

		aux = aux->prox;
	}

	return -1;
}

int TrocaProfessorLISTA(LISTA **inicio, int escola, int atual, int substituto){
    if(ExisteLISTA(inicio) == 0)
		return -1;

	if(ehVaziaLISTA(inicio) == 1)
		return -1;

    LISTA *aux;

    aux = *inicio;

    while(aux != NULL){
        if(aux->id_escola == escola && aux->id_professor == atual){
            aux->id_professor = substituto;
            return 1;
        }

        aux = aux->prox;
    }

    return -1;
}

// Retorna a posição de um elemento
int BuscaLISTA(LISTA **inicio, int elemento){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	int i = 0;

	LISTA *aux;

	aux = *inicio;

	while(aux != NULL){
		if(aux->id_escola == elemento)
			return i;

		i++;

		aux = aux->prox;
	}

	return 0;
}

int RemoveBuscaLISTA(LISTA **inicio, int professor, int escola){
	if(ExisteLISTA(inicio) == 0)
		return 0;

	if(ehVaziaLISTA(inicio) == 1)
		return 0;

	LISTA *aux, *ant;

	aux = *inicio;
	//printf("teste1\n\n");

	if(aux->id_professor == professor && aux->id_escola == escola){
		*inicio = aux->prox;
		free(aux);
		//printf("teste2\n\n");
		return 1;
	}

	while(aux->prox != NULL){
		ant = aux;
		aux = aux->prox;
		//printf("teste3\n\n");


		//printf("teste4\n\n");
		if(aux->id_professor == professor && aux->id_escola == escola){
			ant->prox = aux->prox;
			free(aux);
			//printf("teste5\n\n");
			return 1;
		}

	}
	//printf("teste6\n\n");

	return 0;
}

// Remove o elemento do início da lista
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

// Remove o elemento no final da lista
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
		printf("%d %d => ", aux->id_professor, aux->id_escola);
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
