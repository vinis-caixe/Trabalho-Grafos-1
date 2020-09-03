/*
Trabalho 1 de Teoria e Aplicação de Grafos
Pedro Vitor Valença Mizuno - 17/0043665
Vinícius Caixeta de Souza - 18/0132199

@inproceedings{nr-aaai15,
    title = {The Network Data Repository with Interactive Graph Analytics and Visualization},
    author={Ryan A. Rossi and Nesreen K. Ahmed},
    booktitle = {Proceedings of the Twenty-Ninth AAAI Conference on Artificial Intelligence},
    url={http://networkrepository.com},
    year={2015}
}
*/

// Parte do código foi utilizada a partir do link fornecido pelo professor: http://www2.dcc.ufmg.br/livros/algoritmos-edicao2/cap7/codigo/c/7.4a7.5e7.8-grafolistaap.c

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
    TipoLista Adj[63];
    int NumVertices;
    int NumArestas;
} TipoGrafo;

/* Estrutura dos conjuntos que fazem parte da operação de clique */
typedef struct Clique {
    int Membros[62];    // 62 possíveis membros do conjunto
    int vazio;          // Indica se o conjunto está vazio
} Clique;

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
    fclose(arq);
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

/* Função responsável para inserir as arestas do grafo */
void insere_aresta(int vertice, TipoLista *Lista) {
    Lista->Ultimo->Prox = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Vertice = vertice;
    Lista->Ultimo->Prox = NULL;
}

/* Função responsável para encontrar o grau do grafo */
void encontra_grau(TipoGrafo *Grafo) {
    Apontador aux;
    int grau = 0;
    for(int i = 1; i < Grafo->NumVertices; i++) {
        printf("Golfinho %d: ", i);
        if(Grafo->Adj[i].Primeiro == Grafo->Adj[i].Ultimo) {    // Caso não tenha adjacentes
            printf("0");
        } else {
            aux = Grafo->Adj[i].Primeiro->Prox;
            while(aux != NULL) {    // Até atingir o último vértice adjacente, aumenta o contador do grau
                grau++;
                aux = aux->Prox;
            }
            printf("%d", grau);
            grau = 0;
        }
        printf("\n");
    }
}

/* Função responsável para checar se o conjunto é vazio, caso sim, marca como vazio */
void conjunto_vazio(Clique *conjunto) {
    int contador = 0;
    for(int i = 0; i < 62; i++) {
        if(conjunto->Membros[i] == 0)
            contador++;
    }
    if(contador == 62)
        conjunto->vazio = 1;
}

/* Função responsável para realizar a união de um conjunto e o singleton */
void uniao(Clique *R_ou_X, Clique *AuxR_ou_AuxX, int v, int opcao) {
    int contador = 0;
    if(opcao == 1) {    // Caso salve no auxiliar
        while(R_ou_X->Membros[contador] != 0)
            contador++;
        AuxR_ou_AuxX->Membros[contador] = v;
        AuxR_ou_AuxX->vazio = 0;
    } else if (opcao == 0) {    // Caso salve no original
        while(R_ou_X->Membros[contador] != 0)
            contador++;
        R_ou_X->Membros[contador] = v;
        R_ou_X->vazio = 0;
    }

    // Checa se o original e auxiliar são vazios
    conjunto_vazio(AuxR_ou_AuxX);
    conjunto_vazio(R_ou_X);
}

/* Função responsável para encontrar os adjacentes (vizinhos) do vértice procurado */
void vizinhos_adj(int v, TipoGrafo *Grafo, int vizinhos[20]) {
    Apontador aux = Grafo->Adj[v].Primeiro->Prox;   // aux recebe o primeiro dos vértices adjacentes
    int contador = 0;
    while(aux != NULL) {    // Até aux chegar no último vértice adjacente, grava vizinhos o valor dos vértices
        vizinhos[contador] = aux->Vertice;
        contador++;
        aux = aux->Prox;
    }
}

/* Função responsável para realizar a interseção do conjunto e singleton */
void intersecao(Clique *P_ou_X, Clique *AuxP_ou_AuxX, int v, TipoGrafo *Grafo) {
    int vizinhos[20], contador = 0, n = 0;
    for(int i = 0; i < 20; i++) {
        vizinhos[i] = 0;
    }
    vizinhos_adj(v, Grafo, vizinhos);
    for(int i = 0; i < 62; i++) {
        AuxP_ou_AuxX->Membros[i] = 0;
    }
    AuxP_ou_AuxX->vazio = 1;
    while(vizinhos[contador] != 0) {    // Procura vértices iguais entre vizinhos e P_ou_X
        for(int j = 0; j < 62; j++) {
            if(vizinhos[contador] == P_ou_X->Membros[j]) {  // Se encontra, armazena no auxiliar
                AuxP_ou_AuxX->Membros[n] = vizinhos[contador];
                AuxP_ou_AuxX->vazio = 0;
                n++;
                break;
            }
        }
        contador++;
    }

    // Checa se o original ou auxiliar são vazios
    conjunto_vazio(AuxP_ou_AuxX);
    conjunto_vazio(P_ou_X);
}

/* Função responsável para realizar o complemento entre um conjunto e o singleton */
void complemento(Clique *P, int v) {
    int flag = 0;
    for(int i = 0; i < 62; i++) {   // Procura por um vértice igual ao singleton
        if(P->Membros[i] == v) {
            flag = 1;
        }
        if(flag == 1 && i < 62) {   // Caso encontre, transporta todos os números após o singleton uma casa a esquerda
            P->Membros[i] = P->Membros[i+1];    // Ocupando o espaço que ele antes ocupava
            P->Membros[i+1] = 0;
        }
    }
    P->Membros[61] = 0;

    // Checa se o original é vazio
    conjunto_vazio(P);
}

/* Função responsável para encontrar os cliques maximais */
void BronKerbosch(TipoGrafo *Grafo, Clique *R, Clique *P, Clique *X) {

    Clique AuxR, AuxP, AuxX;    // Cria cliques auxiliares
    AuxR.vazio = R->vazio;
    AuxX.vazio = X->vazio;
    AuxP.vazio = P->vazio;
    for(int i = 0; i < 62; i++) {
        AuxP.Membros[i] = P->Membros[i];
        AuxX.Membros[i] = X->Membros[i];
        AuxR.Membros[i] = R->Membros[i];
    }

    // Caso P e X sejam vazios, existe um clique em R
    if(P->vazio == 1 && X->vazio == 1) {
        int i = 0;
        printf("Clique maximal:");
        while(R->Membros[i] != 0) {
            printf(" %d", R->Membros[i]);
            i++;
        }
        printf("   (%d vertices)", i);
        printf("\n");
    }

    int v = P->Membros[0];
    while(P->vazio == 0 && v != 0) {
        uniao(R, &AuxR, v, 1);
        intersecao(P, &AuxP, v, Grafo);
        intersecao(X, &AuxX, v, Grafo);

        BronKerbosch(Grafo, &AuxR, &AuxP, &AuxX); // Chamada recursiva

        complemento(P, v);
        uniao(X, &AuxX, v, 0);

        if(P->vazio == 0)
            v = P->Membros[0];
    }
}

/* Função responsável por calcular o coeficiente de aglomeração de um vértice */
float CoefDeAglomeracao(TipoGrafo *Grafo, int Golfinho){
    int adjacente;
    float cont = 0, n = 0, Resultado;
    Apontador aux1, aux2, aux3;

    // Calcula quantos vértices são adjacentes ao golfinho
    aux1 = Grafo->Adj[Golfinho].Primeiro->Prox;
    while(aux1 != NULL){
        n++;
        aux1 = aux1->Prox;
    }

    if(n <= 1){
        printf("Golfinho %d: 0.00\n", Golfinho);
        return 0.00;
    }

    aux1 = Grafo->Adj[Golfinho].Primeiro->Prox;
    while(aux1 != NULL){
        adjacente = aux1->Vertice;
        aux2 = aux1->Prox;

        // Calcula quantos vértices adjacentes de um golfinho são também adjacentes a um determinado vértice adjacente
        while(aux2 != NULL){
            aux3 = Grafo->Adj[aux2->Vertice].Primeiro->Prox;

            while(aux3 != NULL){
                if(aux3->Vertice == adjacente){
                    cont++;
                }
                aux3 = aux3->Prox;
            }

            aux2 = aux2->Prox;
        }

        aux1 = aux1->Prox;
    }

    Resultado = cont / (n * ((n-1) / 2));
    printf("Golfinho %d: %.2f\n", Golfinho, Resultado);

    return Resultado;
}

/* Função responsável por calcular o coeficiente médio de aglomeração do grafo */
void MediaDeAglomeracao(TipoGrafo *Grafo){
    float Media = 0;
    int i;

    for(i=1; i<=62; i++){
        Media = Media + CoefDeAglomeracao(Grafo, i);
    }

    Media = Media / 62;

    printf("\nCOEFICIENTE MEDIO DE AGLOMERACAO DO GRAFO: %.2f\n", Media);
}

int main() {
    int vetores[159][2];
    le_arquivo(vetores);

    TipoGrafo Grafo;

    Grafo.NumVertices = 63;
    Grafo.NumArestas = 159;

    cria_grafo_vazio(&Grafo);

    for(int i = 0; i < 159; i++) {
        insere_aresta(vetores[i][1], &Grafo.Adj[vetores[i][0]]);
        insere_aresta(vetores[i][0], &Grafo.Adj[vetores[i][1]]);
    }

    printf("\n\n---------- GRAU DOS VERTICES ----------\n");
    encontra_grau(&Grafo);

    printf("\n\n---------- CLIQUES MAXIMAIS ----------\n");
    Clique R, P, X;
    R.vazio = 1;
    X.vazio = 1;
    P.vazio = 0;
    for(int i = 1; i < 63; i++) {
        P.Membros[i-1] = i;
        X.Membros[i-1] = 0;
        R.Membros[i-1] = 0;
    }

    BronKerbosch(&Grafo, &R, &P, &X);

    printf("\n\n---------- COEFICIENTE DE AGLOMERACAO ----------\n");
    MediaDeAglomeracao(&Grafo);

    libera_grafo(&Grafo);

    return 0;
}
