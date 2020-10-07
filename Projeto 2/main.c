#include "fila.h"
#include "lista.h"
#include <string.h>

/*Função responsável por criar as listas de adjacências*/
void cria_lista_vazia(TipoLista *Lista, char codigo[], int peso, int id) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    strcpy(Lista->Codigo_Vertice, codigo);    // Armazenamos o código da disciplina
    Lista->Peso_Vertice = peso;
    Lista->Id_Vertice = id;
    Lista->Primeiro->Prox = NULL;
}

/*Função responsável por criar o grafo, enviando o código da disciplina para identificação*/
void cria_grafo_vazio(TipoGrafo *Grafo) {
    char codigos[32][8] = {"CIC0003", "CIC0004", "CIC0142", "MAT0025",
    "CIC0002", "CIC0090", "CIC0229", "CIC0231",
    "MAT0026", "MAT0031", "CIC0098", "CIC0197",
    "EST0023", "MAT0034", "MAT0053", "CIC0124",
    "CIC0182", "CIC0198", "CIC0199", "CIC0093",
    "CIC0097", "CIC0105", "CIC0135", "CIC0202",
    "CIC0101", "CIC0104", "CIC0161", "CIC0203",
    "CIC0205", "CIC0189", "CIC0201", "CIC0204"};
    int pesos[32] = {4, 6, 2, 6, 4, 4, 4, 2, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 4, 4, 4, 4, 4};
    for(int i = 0; i < Grafo->NumVertices; i++)
        cria_lista_vazia(&Grafo->Adj[i], codigos[i], pesos[i], i);
}

/*Função que insere os valores respectivos a cada aresta*/
void insere_aresta(int id, char codigo[], int peso, TipoLista *Lista) {
    Lista->Ultimo->Prox = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Id = id;
    strcpy(Lista->Ultimo->Codigo, codigo);
    Lista->Ultimo->Peso = peso;
    Lista->Ultimo->Prox = NULL;
}

/*Função que realiza chamadas com os valores para serem armazenados nas arestas*/
void monta_grafo(TipoGrafo *Grafo) {
    insere_aresta(5, "CIC0090", 4, &Grafo->Adj[1]);
    insere_aresta(6, "CIC0229", 4, &Grafo->Adj[1]);
    insere_aresta(7, "CIC0231", 2, &Grafo->Adj[1]);
    insere_aresta(8, "MAT0026", 6, &Grafo->Adj[3]);
    insere_aresta(10, "CIC0098", 4, &Grafo->Adj[6]);
    insere_aresta(10, "CIC0098", 4, &Grafo->Adj[7]);
    insere_aresta(11, "CIC0197", 4, &Grafo->Adj[5]);
    insere_aresta(12, "EST0023", 4, &Grafo->Adj[3]);
    insere_aresta(14, "MAT0026", 4, &Grafo->Adj[8]);
    insere_aresta(15, "CIC0124", 4, &Grafo->Adj[5]);
    insere_aresta(16, "CIC0182", 4, &Grafo->Adj[5]);
    insere_aresta(17, "CIC0198", 4, &Grafo->Adj[11]);
    insere_aresta(18, "CIC0199", 4, &Grafo->Adj[5]);
    insere_aresta(19, "CIC0093", 4, &Grafo->Adj[5]);
    insere_aresta(21, "CIC0105", 4, &Grafo->Adj[11]);
    insere_aresta(22, "CIC0135", 4, &Grafo->Adj[5]);
    insere_aresta(23, "CIC0202", 4, &Grafo->Adj[10]);
    insere_aresta(23, "CIC0202", 4, &Grafo->Adj[17]);
    insere_aresta(24, "CIC0101", 4, &Grafo->Adj[5]);
    insere_aresta(25, "CIC0104", 4, &Grafo->Adj[5]);
    insere_aresta(26, "CIC0161", 6, &Grafo->Adj[13]);
    insere_aresta(27, "CIC0203", 4, &Grafo->Adj[12]);
    insere_aresta(27, "CIC0203", 4, &Grafo->Adj[5]);
    insere_aresta(28, "CIC0205", 4, &Grafo->Adj[23]);
    insere_aresta(29, "CIC0189", 4, &Grafo->Adj[3]);
    insere_aresta(29, "CIC0189", 4, &Grafo->Adj[5]);
    insere_aresta(30, "CIC0201", 4, &Grafo->Adj[15]);
    insere_aresta(31, "CIC0204", 4, &Grafo->Adj[19]);
    insere_aresta(31, "CIC0204", 4, &Grafo->Adj[25]);
    insere_aresta(31, "CIC0204", 4, &Grafo->Adj[26]);
}

void monta_grafo_reverso(TipoGrafo *Grafo, TipoGrafo *Reverso) {
    Apontador aux;
    for(int i = 0; i < 32; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        while(aux != NULL){
            insere_aresta(i, Grafo->Adj[i].Codigo_Vertice, Grafo->Adj[i].Peso_Vertice, &Reverso->Adj[aux->Id]);
            aux = aux->Prox;
        }
    }
}

/*Função responsável pela impressão do DAG*/
void imprime_grafo(TipoGrafo *Grafo) {
    Apontador Aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        printf("%s: ", Grafo->Adj[i].Codigo_Vertice);
        if(Grafo->Adj[i].Primeiro != Grafo->Adj[i].Ultimo) {    // Se não for vazio
            Aux = Grafo->Adj[i].Primeiro->Prox;
            while(Aux != NULL) {
                printf("%s %d -> ", Aux->Codigo, Aux->Peso);
                Aux = Aux->Prox;
            }
        }
        printf("NULL\n\n");
    }
}

/*Função que encontra os graus de chegada dos vértices*/
void encontra_grau(TipoGrafo *Grafo, int graus_chegada[], int graus_saida[]) {
    Apontador aux;
    int i;
    for(i = 0; i < 32; i++){
        graus_chegada[i] = 0;   // Vetores de 32 espaços armazenando o grau de entrada e saída dos 32 vértices
        graus_saida[i] = 0;
    }

    for(i = 0; i < 32; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        while(aux != NULL) {
            graus_chegada[aux->Id]++;   // Aumenta o grau de chegada do vértice a medida que encontra adjacências
            graus_saida[i]++;   // Aumenta o grau de saida do vértice de acordo com os seus adjacentes
            aux = aux->Prox;
        }
    }
}

/*Algorítmo responsável por encontrar a ordenação topológica do DAG*/
void algoritmo_Kahn(TipoGrafo *Grafo, int graus_chegada[]) {
    FILA **fila;
    int contador = 0, i;

    fila = criaFILA();

    // Se o grau de chegada do vértice for 0 ele é colocado no final da fila
    for(i = 0; i < 32; i++) {
        if(graus_chegada[i] == 0) {
            enfileirar(fila, Grafo->Adj[i]);
            graus_chegada[i] = -1;  // Marca como já enfileirado
        }
    }

    Apontador aux;

    while(!ehVaziaFILA(fila)){  // Se a fila não for vazia
        TipoLista vertice_removido = primeiroFILA(fila);
        desenfileirar(fila);
        printf("%s\n", vertice_removido.Codigo_Vertice);  // Remove o primeiro da fila e printa seu código
        contador++;
        for(i = 0; i < 32; i++) {
            if(!(strcmp(vertice_removido.Codigo_Vertice, Grafo->Adj[i].Codigo_Vertice))){   // Se o código do removido for igual ao código do vértice agora testado
                aux = Grafo->Adj[i].Primeiro->Prox;
                while(aux != NULL) {
                    graus_chegada[aux->Id]--;   // Diminui o grau dos adjacentes ao vértice atual
                    if(graus_chegada[aux->Id] == 0) {
                        enfileirar(fila, Grafo->Adj[aux->Id]);  // Enfileira o atual
                        graus_chegada[aux->Id] = -1;    // Marca como já enfileirado
                    }
                    aux = aux->Prox;
                }
                break;
            }
        }
    }

    if(contador != 32)
        printf("Nao eh possivel ter uma ordem topologica\n");
    
    liberaFILA(fila);
}

void tres_caminhos_criticos(LISTA **caminho_critico, int peso_critico, int tres_PC[], int tres_CC[3][6]) {
    int vertices_CC[18], k, repete = -1, i, menor_PC = 99, menor_i;
    for(i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            vertices_CC[6*i + j] = tres_CC[i][j];
        }
    }
    for(i = 0; i < 18; i++) {
        k = 0;
        while(PosicaoLISTA(caminho_critico, k) != -1) {
            if(vertices_CC[i] == PosicaoLISTA(caminho_critico, k)) {
                repete = i;
            }
            k++;
        }
    }
    if(repete == -1) {  // se nao repete
        for(i = 0; i < 3; i++) {
            if(menor_PC > tres_PC[i]) {
                menor_PC = tres_PC[i];
                menor_i = i;
            }
        }
        for(i = 0; i < 6; i++) {
            if(PosicaoLISTA(caminho_critico, i) != -1) {
                vertices_CC[6*menor_i + i] = PosicaoLISTA(caminho_critico, i);
            } else
                vertices_CC[6*menor_i + i] = 0;
        }
        tres_PC[menor_i] = peso_critico;
    } else {
        if(tres_PC[repete/6] < peso_critico) {
            tres_PC[repete/6] = peso_critico;
            for(i = 0; i < 6; i++) {
                if(PosicaoLISTA(caminho_critico, i) != -1) {
                    vertices_CC[(repete-(repete%6)) + i] = PosicaoLISTA(caminho_critico, i);
                }
                else
                    vertices_CC[(repete-(repete%6)) + i] = 0;
            }
        }
    }
    for(i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            tres_CC[i][j] = vertices_CC[6*i + j];
        }
    }
}

void recursao_backflow(TipoGrafo *Reverso, TipoLista Vertice, int peso_critico, int peso_local, LISTA **caminho_critico, int tres_PC[], int tres_CC[3][6]) {
    Apontador aux;
    if(Vertice.Primeiro->Prox == NULL && peso_local > peso_critico) {
        peso_critico = peso_local;
        tres_caminhos_criticos(caminho_critico, peso_critico, tres_PC, tres_CC);
    } else {
        aux = Vertice.Primeiro->Prox;
        while(aux != NULL) {
            peso_local += aux->Peso;
            InsereFinalLISTA(caminho_critico, aux->Id);
            recursao_backflow(Reverso, Reverso->Adj[aux->Id], peso_critico, peso_local, caminho_critico, tres_PC, tres_CC);
            aux = aux->Prox;
            peso_local -= Vertice.Peso_Vertice;
            RemoveFinalLISTA(caminho_critico);
        }
    }
    peso_local -= Vertice.Peso_Vertice;
}

void algoritmo_backflow(TipoGrafo *Grafo, TipoGrafo *Reverso, int graus_saida[], int tres_PC[], int tres_CC[3][6]) {
    int peso_critico = 0, peso_local = 0;
    LISTA **caminho_critico;
    caminho_critico = CriaIniciaLISTA();
    for(int i = 0; i < 32; i++) {
        if(graus_saida[i] == 0) {   // Se é um dos vértices finais
            peso_local += Reverso->Adj[i].Peso_Vertice;
            InsereFinalLISTA(caminho_critico, Reverso->Adj[i].Id_Vertice);
            recursao_backflow(Reverso, Reverso->Adj[i], peso_critico, peso_local, caminho_critico, tres_PC, tres_CC);
            RemoveFinalLISTA(caminho_critico);
        }
        peso_local = 0;
        peso_critico = 0;
    }

    LiberaLISTA(caminho_critico);
}

/*Função responsável por liberar a memória alocada pelo DAG*/
void libera_grafo(TipoGrafo *Grafo) {
    Apontador anterior, aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        free(Grafo->Adj[i].Primeiro);
        Grafo->Adj[i].Primeiro = NULL;
        while(aux != NULL) {
            anterior = aux;
            aux = aux->Prox;
            free(anterior);
        }
    }
}

void gera_dot(TipoGrafo *Grafo) {
    FILE *arq = fopen("grafo.dot", "w");
    if(arq == NULL) {
        printf("Erro ao criar o arquivo\n");
    }
    

    fclose(arq);
}

int main(){

    TipoGrafo Grafo;
    Grafo.NumVertices = 32;
    Grafo.NumArestas = 30;
    
    int graus_chegada[32], graus_saida[32];

    cria_grafo_vazio(&Grafo);

    monta_grafo(&Grafo);

    printf("\n\n-----BACHARELADO EM CIENCIA DA COMPUTACAO-----\n\n------DAG------\n");

    imprime_grafo(&Grafo);

    encontra_grau(&Grafo, graus_chegada, graus_saida);

    printf("\n------ORDENACAO TOPOLOGICA------\n\n");
    algoritmo_Kahn(&Grafo, graus_chegada);

    encontra_grau(&Grafo, graus_chegada, graus_saida);

    TipoGrafo Grafo_Reverso;
    Grafo_Reverso.NumVertices = 32;
    Grafo_Reverso.NumArestas = 30;
    
    cria_grafo_vazio(&Grafo_Reverso);
    monta_grafo_reverso(&Grafo, &Grafo_Reverso);

    int tres_PC[3], tres_CC[3][6];
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++)
            tres_CC[i][j] = 0;
        tres_PC[i] = 0;
    }

    printf("\n---TRES MAIORES CAMINHOS CRITICOS COM VERTICES DIFERENTES---\n\n");

    algoritmo_backflow(&Grafo, &Grafo_Reverso, graus_saida, tres_PC, tres_CC);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            if(tres_CC[i][j] != 0) {
                printf("%s%d ", j != 0 ? "<- " : "", tres_CC[i][j]);
            }
        }
        printf("Peso total: %d\n", tres_PC[i]);
    }
    
    libera_grafo(&Grafo);

    libera_grafo(&Grafo_Reverso);
    return 0;
}
