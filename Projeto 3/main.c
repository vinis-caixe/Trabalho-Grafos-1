#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Estrutura de cada uma das células adjacentes*/
typedef struct Struct_Celula *Apontador;
struct Struct_Celula {
    int Id_Adjacente;
    Apontador Prox;
};
typedef struct Struct_Celula Celula;

/* Estrutura da lista */
typedef struct TipoLista {
    int Id;
    int Habilitacao;
    int Segunda_Habilitacao;
    Apontador Primeiro, Ultimo;
} TipoLista;

/* Estrutura do grafo*/
typedef struct TipoGrafo {
    TipoLista Adj[151];
    int NumVertices;
    int NumArestas;
} TipoGrafo;

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

/* Função responsável para inserir as arestas do grafo */
void insere_aresta(int id, TipoLista *Lista) {
    Lista->Ultimo->Prox = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Id_Adjacente = id;
    Lista->Ultimo->Prox = NULL;
}

/*Função responsável pela impressão do DAG*/
void imprime_grafo(TipoGrafo *Grafo) {
    Apontador Aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        //printf("%s: ", Grafo->Adj[i].Codigo_Vertice);
        if(Grafo->Adj[i].Primeiro != Grafo->Adj[i].Ultimo) {    // Se não for vazio
            Aux = Grafo->Adj[i].Primeiro->Prox;
            while(Aux != NULL) {
                //printf("%s %d -> ", Aux->Codigo, Aux->Peso);
                Aux = Aux->Prox;
            }
        }
        printf("NULL\n\n");
    }
}

void leitura_arq(int habilitacoes[]) {
    char linha[110];
    int i, num_dois_pontos, pos_dois_pontos[2], contador_escola = 101;    
    FILE *arq = fopen("entradaProj3TAG.txt", "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int id = 1;
    while(!feof(arq)) {
        i = 0;

        fgets(linha, 110, arq);

        if(linha[0] == '(') {
            //printf("%s", linha);
            if(id <= 100) {     // Lendo habilitacoes dos professores
                while(linha[i] != ',')
                    i++;

                habilitacoes[id-1] = (int)linha[i+2] - 48;
            } else {
                num_dois_pontos = 0;
                while(linha[i] != '\0') {
                    if(linha[i] == ':') {
                        pos_dois_pontos[num_dois_pontos] = i;
                        num_dois_pontos++;
                    }
                    i++;
                }
                habilitacoes[contador_escola-1] = (int)linha[pos_dois_pontos[0]+2] - 48;
                if(num_dois_pontos == 2) {
                    habilitacoes[contador_escola] = (int)linha[pos_dois_pontos[1]+2] - 48;
                    contador_escola++;
                }
                contador_escola++;
            }
            id++;
        }
    }

    fclose(arq);
}
int main() {
    int habilitacoes[184];
    leitura_arq(habilitacoes);

    for(int i = 0; i < 184; i++)
        printf("%d\n", habilitacoes[i]);

    TipoGrafo Grafo;
    Grafo.NumVertices = 150;
    Grafo.NumArestas = 382;

    //cria_grafo_vazio(&Grafo);

    return 0;
}