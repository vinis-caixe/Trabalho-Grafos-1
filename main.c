/*
Trabalho 1 de Teoria e Aplicação de Grafos
Pedro Vitor Valença Mizuno - 17/0043665

@inproceedings{nr-aaai15,
    title = {The Network Data Repository with Interactive Graph Analytics and Visualization},
    author={Ryan A. Rossi and Nesreen K. Ahmed},
    booktitle = {Proceedings of the Twenty-Ninth AAAI Conference on Artificial Intelligence},
    url={http://networkrepository.com},
    year={2015}
}
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura de cada uma das células adjacentes*/
typedef struct Struct_Celula *Apontador;
struct Struct_Celula {
  int Vertice;
  Apontador Prox;
}; 
typedef struct Struct_Celula Celula;

/* Estrutura da lista */
typedef struct TipoLista {
  Apontador Primeiro, Ultimo;
} TipoLista;

/* Estrutura do grafo*/
typedef struct TipoGrafo {
  TipoLista Adj[62];    // Lista dos adjacentes
  int NumVertices;
  int NumArestas;
} TipoGrafo;

/* Função responsável pela transformação dos dados lidos no arquivo em inteiros, armazenados na matriz vetores*/
void transforma_em_int(int vetores[159][2], FILE *arq) {
    char linha[100];
    int flag_do_cabecalho = 0, i = 0, j = 0;

    while(fgets(linha, sizeof(linha), arq)) {
        if(linha[0] != '%'){                        // Ignora comentários
            if(flag_do_cabecalho == 1) {            // Ignora o cabeçalho dos dados
                char *numero = strtok(linha, " ");
                while(numero) {
                    vetores[i][j] = atoi(numero);
                    numero = strtok(NULL, " ");
                    j++;
                }
                j = 0;
                i++;
            }
            flag_do_cabecalho = 1;
        }
    }
}

/* Função responsável pela leitura do arquivo */
void le_arquivo(int vetores[159][2]) {
    FILE *arq;
    arq = fopen("soc-dolphins.mtx", "r");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    transforma_em_int(vetores, arq);
}

/* Função responsável por criar a lista de adjacentes */
void cria_lista_vazia(TipoLista *Lista) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Primeiro->Prox = NULL;
}

/* Função responsável por criar o grafo vazio */
void cria_grafo_vazio(TipoGrafo *Grafo) {
    for(int i = 0; i < Grafo->NumVertices; i++)
        cria_lista_vazia(&Grafo->Adj[i]);
}

/* Função responsável por desalocar a memória usada no grafo */
void libera_grafo(TipoGrafo *Grafo) {
    Apontador anterior, aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        free(Grafo->Adj[i].Primeiro);   // Libera o primeiro elemento
        Grafo->Adj[i].Primeiro = NULL;
        while(aux != NULL) {            // Libera os demais, até que não existam outros
            anterior = aux;
            aux = aux->Prox;
            free(anterior);
        }
    }
}

int main() {
    int vetores[159][2];
    le_arquivo(vetores);

/*    for(int i = 0; i < 159; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", vetores[i][j]);
        }
        printf("\n");
    }*/

    TipoGrafo Grafo;
    
    Grafo.NumVertices = 62;
    Grafo.NumArestas = 159;

    cria_grafo_vazio(&Grafo);

    libera_grafo(&Grafo);

    return 0;
}