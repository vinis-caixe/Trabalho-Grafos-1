#include "fila.h"
#include "lista.h"
#include <string.h>

/*Função responsável por criar as listas de adjacências*/
void cria_lista_vazia(TipoLista *Lista, char codigo[], int peso, int id, char nome[]) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    strcpy(Lista->Codigo_Vertice, codigo);    // Armazenamos o código da disciplina
    Lista->Peso_Vertice = peso;
    Lista->Id_Vertice = id;
    strcpy(Lista->Nome_Vertice, nome);
    Lista->Primeiro->Prox = NULL;
}

/*Função responsável por criar o grafo, enviando o código da disciplina para identificação*/
void cria_grafo_vazio(TipoGrafo *Grafo) {
    char codigos[32][7] = {"113468", "113476", "116726", "113034",
    "113450", "116319", "129011", "129020",
    "113042", "113093", "116394", "117889",
    "115045", "113107", "113417", "116572",
    "117366", "117897", "117901", "116343",
    "116378", "116441", "116653", "117935",
    "116416", "116432", "116882", "117943",
    "117960", "117536", "117927", "117951"};
    char nomes[32][42] = {"INTRODUCAO AOS SISTEMAS COMPUTACIONAIS", "ALGORITMOS E PROGRAMACAO DE COMPUTADORES", "INFORMATICA E SOCIEDADE", "CALCULO 1",
    "FUNDAMENTOS TEORICOS DA COMPUTACAO", "ESTRUTURAS DE DADOS", "CIRCUITOS LOGICOS", "LABORATORIO DE CIRCUITOS LOGICOS", "CALCULO 2",
    "INTRODUCAO A ALGEBRA LINEAR", "ORGANIZACAO E ARQUITETURA DE COMPUTADORES", "TECNICAS DE PROGRAMACAO 1", "PROBABILIDADE E ESTATISTICA",
    "ALGEBRA 1", "CALCULO NUMERICO", "REDES DE COMPUTADORES",
    "LOGICA COMPUTACIONAL 1", "TECNICAS DE PROGRAMACAO 2", "TEORIA E APLICACAO DE GRAFOS",
    "LINGUAGENS DE PROGRAMACAO", "BANCOS DE DADOS", "ENGENHARIA DE SOFTWARE",
    "INTRODUCAO A INTELIGENCIA ARTIFICIAL", "PROGRAMACAO CONCORRENTE", "SISTEMAS DE INFORMACAO", "SOFTWARE BASICO",
    "AUTOMATOS E COMPUTABILIDADE", "COMPUTACAO EXPERIMENTAL", "FUNDAMENTOS DE SISTEMAS OPERACIONAIS",
    "PROJETO E ANALISE DE ALGORITMOS", "SEGURANCA COMPUTACIONAL", "COMPILADORES"};   
    int pesos[32] = {4, 6, 2, 6, 4, 4, 4, 2, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 4, 4, 4, 4, 4};
    for(int i = 0; i < Grafo->NumVertices; i++)
        cria_lista_vazia(&Grafo->Adj[i], codigos[i], pesos[i], i, nomes[i]);
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
    insere_aresta(5, "116319", 4, &Grafo->Adj[1]);
    insere_aresta(6, "129011", 4, &Grafo->Adj[1]);
    insere_aresta(7, "129020", 2, &Grafo->Adj[1]);
    insere_aresta(8, "113042", 6, &Grafo->Adj[3]);
    insere_aresta(10, "116394", 4, &Grafo->Adj[6]);
    insere_aresta(10, "116394", 4, &Grafo->Adj[7]);
    insere_aresta(11, "117889", 4, &Grafo->Adj[5]);
    insere_aresta(12, "115045", 4, &Grafo->Adj[3]);
    insere_aresta(14, "113417", 4, &Grafo->Adj[8]);
    insere_aresta(15, "116572", 4, &Grafo->Adj[5]);
    insere_aresta(16, "117366", 4, &Grafo->Adj[5]);
    insere_aresta(17, "117897", 4, &Grafo->Adj[11]);
    insere_aresta(18, "117901", 4, &Grafo->Adj[5]);
    insere_aresta(19, "116343", 4, &Grafo->Adj[5]);
    insere_aresta(21, "116441", 4, &Grafo->Adj[11]);
    insere_aresta(22, "116653", 4, &Grafo->Adj[5]);
    insere_aresta(23, "117935", 4, &Grafo->Adj[10]);
    insere_aresta(23, "117935", 4, &Grafo->Adj[17]);
    insere_aresta(24, "116416", 4, &Grafo->Adj[5]);
    insere_aresta(25, "116432", 4, &Grafo->Adj[5]);
    insere_aresta(26, "116882", 6, &Grafo->Adj[13]);
    insere_aresta(27, "117943", 4, &Grafo->Adj[12]);
    insere_aresta(27, "117943", 4, &Grafo->Adj[5]);
    insere_aresta(28, "117960", 4, &Grafo->Adj[23]);
    insere_aresta(29, "117536", 4, &Grafo->Adj[3]);
    insere_aresta(29, "117536", 4, &Grafo->Adj[5]);
    insere_aresta(30, "117927", 4, &Grafo->Adj[15]);
    insere_aresta(31, "117951", 4, &Grafo->Adj[19]);
    insere_aresta(31, "117951", 4, &Grafo->Adj[25]);
    insere_aresta(31, "117951", 4, &Grafo->Adj[26]);
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

void cria_dot(TipoGrafo *Grafo, int tres_CC[3][6]) {
    FILE *arq = fopen("grafo.dot", "w");
    if(arq == NULL) {
        printf("Erro ao criar o arquivo\n");
    }

    fprintf(arq, "digraph projeto {\n");
    
    Apontador aux;
    for(int i = 0; i < 32; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        if(aux == NULL) {
            fprintf(arq, "\t%s;\n", Grafo->Adj[i].Codigo_Vertice);
        }
        else {
            while(aux != NULL) {
                fprintf(arq, "\t%s -> %s;\n", Grafo->Adj[i].Codigo_Vertice, aux->Codigo);   
                aux = aux->Prox;
            }
        }
       
    }

    fprintf(arq, "}");
    fclose(arq);
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

int main(){

    TipoGrafo Grafo;
    Grafo.NumVertices = 32;
    Grafo.NumArestas = 30;
    
    int graus_chegada[32], graus_saida[32];

    cria_grafo_vazio(&Grafo);

    monta_grafo(&Grafo);

    printf("\n\n-----BACHARELADO EM CIENCIA DA COMPUTACAO-----\n\n------CURSOS E SEUS CODIGOS------\n");

    for(int i = 0; i < 32; i++){
        printf("CURSO: %s\nCODIGO: %s\n\n", Grafo.Adj[i].Nome_Vertice, Grafo.Adj[i].Codigo_Vertice);
    }

    printf("\n------DAG------\n\n");
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

    printf("\n\n---TRES MAIORES CAMINHOS CRITICOS COM VERTICES DIFERENTES---\n\nCODIGO PESO\n");

    algoritmo_backflow(&Grafo, &Grafo_Reverso, graus_saida, tres_PC, tres_CC);

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            if(tres_CC[i][j] != 0) {
                printf("%s%s %d ", j != 0 ? "<- " : "", Grafo.Adj[tres_CC[i][j]].Codigo_Vertice, Grafo.Adj[tres_CC[i][j]].Peso_Vertice);
            }
        }
        printf("\tPeso total: %d\n", tres_PC[i]);
    }

    cria_dot(&Grafo, tres_CC);
    
    libera_grafo(&Grafo);

    libera_grafo(&Grafo_Reverso);
    return 0;
}
