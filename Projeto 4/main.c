/*
Trabalho 4 de Teoria e Aplicação de Grafos
Pedro Vitor Valença Mizuno - 17/0043665
Vinícius Caixeta de Souza - 18/0132199
*/

// Parte do código de montagem do grafo foi utilizada a partir do link fornecido pelo professor:
// http://www2.dcc.ufmg.br/livros/algoritmos-edicao2/cap7/codigo/c/7.4a7.5e7.8-grafolistaap.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"

/* Estrutura de cada uma das células adjacentes*/
typedef struct Struct_Celula *Apontador;
struct Struct_Celula {
    int Id;
    Apontador Prox;
};
typedef struct Struct_Celula Celula;

/* Estrutura da lista de adjacencias */
typedef struct TipoLista {
    Apontador Primeiro, Ultimo;
    int Codigo_Vertice;
    int Peso_Vertice;
    char Nome_Vertice[42];
    int Semestre;
    int Horarios[3];
} TipoLista;

/* Estrutura do grafo */
typedef struct TipoGrafo {
    TipoLista Adj[31];  // 31 ou 32?
    int NumVertices;
    int NumArestas;
} TipoGrafo;

/**
 *  Função responsável por criar a lista de adjacência (ainda sem arestas)
 *  @param Lista lista de adjacência
 *  @param codigo código da matéria no MatriculaWeb
 *  @param peso número de créditos da matéria
 *  @param nome nome da matéria
 *  @param semestre semestre ao qual a matéria pertence
 */
void cria_lista_vazia(TipoLista *Lista, int codigo, int peso, char nome[], int semestre) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Codigo_Vertice = codigo;
    Lista->Peso_Vertice = peso;
    strcpy(Lista->Nome_Vertice, nome);
    Lista->Semestre = semestre;
    for(int i = 0; i < 3; i++)
        Lista->Horarios[i] = 0;
    Lista->Primeiro->Prox = NULL;
}

/**
 *  Função responsável por enviar os valores a serem armazenados nos vértices
 *  @param Grafo grafo sobre o qual será operado
 */
void cria_grafo_vazio(TipoGrafo *Grafo) {
    int codigos[31] = {113468, 113476, 113034, 113450, 116319, 113042,
    113093, 116394, 117889, 115045, 113107, 113417, 116572, 117366,
    117897, 117901, 116343, 116378,116441, 116653, 117935, 116416,
    116432, 116882, 117943, 117960, 116726, 117536, 117927, 117951, 117919};
    char nomes[31][42] = {"INTRODUCAO AOS SISTEMAS COMPUTACIONAIS", "ALGORITMOS E PROGRAMACAO DE COMPUTADORES", "CALCULO 1",
    "FUNDAMENTOS TEORICOS DA COMPUTACAO", "ESTRUTURAS DE DADOS", "CALCULO 2", "INTRODUCAO A ALGEBRA LINEAR", 
    "ORGANIZACAO E ARQUITETURA DE COMPUTADORES", "TECNICAS DE PROGRAMACAO 1", "PROBABILIDADE E ESTATISTICA", "ALGEBRA 1", "CALCULO NUMERICO", 
    "REDES DE COMPUTADORES", "LOGICA COMPUTACIONAL 1", "TECNICAS DE PROGRAMACAO 2", "TEORIA E APLICACAO DE GRAFOS",
    "LINGUAGENS DE PROGRAMACAO", "BANCOS DE DADOS", "ENGENHARIA DE SOFTWARE", "INTRODUCAO A INTELIGENCIA ARTIFICIAL", "PROGRAMACAO CONCORRENTE", 
    "SISTEMAS DE INFORMACAO", "SOFTWARE BASICO", "AUTOMATOS E COMPUTABILIDADE", "COMPUTACAO EXPERIMENTAL", "FUNDAMENTOS DE SISTEMAS OPERACIONAIS",
    "INFORMATICA E SOCIEDADE", "PROJETO E ANALISE DE ALGORITMOS", "SEGURANCA COMPUTACIONAL", "COMPILADORES",
    "METODOLOGIA CIENTIFICA"};   
    int pesos[31] = {4, 6, 6, 4, 4, 6, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 6, 4, 4, 2, 4, 4, 4, 2};
    int semestre[31] = {1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 8};
    for(int i = 0; i < Grafo->NumVertices; i++)
        cria_lista_vazia(&Grafo->Adj[i], codigos[i], pesos[i], nomes[i], semestre[i]);
}

/**
 *  Função responsável por criar as arestas entre os vértices
 *  @param id identificador da elemento adjacente ao vértice atual
 *  @param Lista vértice de onde será criada a aresta
 */
void insere_aresta(int id, TipoLista *Lista) {
    Lista->Ultimo->Prox = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Id = id;
    Lista->Ultimo->Prox = NULL;
}

/**
 *  Função responsável por ler as arestas no arquivo arestas.txt
 *  @param Grafo grafo sobre o qual será operado
 */
void monta_grafo(TipoGrafo *Grafo) {
    char linha[22];
    int numeros[2], i = 0;
    FILE *arq = fopen("arestas.txt", "r");

    if(arq == NULL) {
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    while(!feof(arq)) {
        fgets(linha, 22, arq);
        if(linha[0] != '/') {   // Ignora comentários
            char *numero = strtok(linha, " ");
            while(numero) {
                numeros[i] = atoi(numero);
                numero = strtok(NULL, " ");
                i++;
            }
            // Realiza chamadas para inserir as arestas entre os vértices
            insere_aresta(numeros[1], &Grafo->Adj[numeros[0]]);
            insere_aresta(numeros[0], &Grafo->Adj[numeros[1]]);
            i = 0;
        }
    }

    fclose(arq);
}

/**
 *  Função responsável por desalocar a memória usada no grafo
 *  @param Grafo grafo sobre o qual será operado
 */
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

/**
 *  Função responsável por imprimir determinada matéria e seus respectivos horários
 *  @param Grafo grafo sobre o qual será operado
 *  @param i determina o id da matéria
*/
void imprime_passos(TipoGrafo *Grafo, int i) {
    char horarios_unb[20][8] = {"SEG 08h", "SEG 10h", "TER 08h", "TER 10h", "QUA 08h", "QUA 10h", "QUI 08h", "QUI 10h", "SEX 08h", 
    "SEX 10h", "SEG 14h", "SEG 16h", "TER 14h", "TER 16h", "QUA 14h", "QUA 16h", "QUI 14h", "QUI 16h", "SEX 14h", "SEX 16h"};

    printf("%d - %s:\n", Grafo->Adj[i].Codigo_Vertice, Grafo->Adj[i].Nome_Vertice);
    int num_aulas = Grafo->Adj[i].Peso_Vertice / 2, cont = 0; // Cada aula de uma matéria possui 2 créditos
    while(cont != num_aulas) {
        printf("\t%s\t", horarios_unb[Grafo->Adj[i].Horarios[cont]]);
        cont++;
    }
    printf("\n\n");
}

/**
 *  Função responsável por imprimir a alocação final em um formato de calendário
 *  @param Grafo grafo sobre o qual será operado
 *  @param Lista lista que contém os horários (cores) já usados pelos adjacentes
 *  @param semestre variável que contém o semestre 
 */
void imprime_alocacao_final(TipoGrafo *Grafo, LISTA **lista, int semestre) {
    printf("----- ALOCACAO FINAL DO %do SEMESTRE -----\n\n\t\tSEG\tTER\tQUA\tQUI\tSEX\n", semestre);
    char horas[4][12] = {"08h00-09h50", "10h00-11h50", "14h00-15h50", "16h00-17h50"};
    
    for(int i = 0; i < 4; i++){
        printf("%s\t", horas[i]);
        for(int j = 0; j < 9; j += 2){
            // Se for um horário da tarde e ele estiver na lista
            if(i > 1 && ExisteElemento(lista, j+i+8))
                printf("%d\t", BuscaCodigo(lista, j+i+8));  // Imprime o código da matéria

            // Se for um horário da manhã e ele estiver na lista
            else if(i <= 1 && ExisteElemento(lista, j+i))
                printf("%d\t", BuscaCodigo(lista, j+i));
            
            else
                printf("\t");
        }
        printf("\n");
    }
}

/**
 *  Função responsável pela coloração do grafo
 *  @param Grafo grafo sobre o qual será operado
 *
 * Serão priorizados horários da manhã.
 * Os números que definem os horários das matérias seguem essa ordem:
 * 
 *                  SEG     TER     QUA     QUI     SEX
 * 08h00-09h50      0       2       4       6       8
 * 10h00-11h50      1       3       5       7       9
 * 14h00-15h50      10      12      14      16      18
 * 16h00-17h50      11      13      15      17      19
 */
void algoritmo_guloso(TipoGrafo *Grafo) {

    // Cria uma lista que contém os horários já ocupados pelos adjacentes
    LISTA **lista;
    lista = CriaIniciaLISTA();
    int semestre = 0, horario = 0, num_aulas, cont = 0;

    // Sobre os 31 vértices, é seguida a ordem na lista de adjacência
    for(int i = 0; i < 31; i++) {

        // A cada mudança de semestre
        if(semestre != Grafo->Adj[i].Semestre) {
            // Imprime a alocação final do semestre
            if(semestre != 0)
                imprime_alocacao_final(Grafo, lista, semestre);

            LimpaLISTA(lista);  // Retira os elementos da lista
            semestre = Grafo->Adj[i].Semestre;  // Atualiza o semestre
            printf("\n----- PASSO A PASSO DO %do SEMESTRE -----\n\n", semestre);
        }
        
        num_aulas = Grafo->Adj[i].Peso_Vertice / 2;
        // Repete de acordo com o número de aulas semanais da matéria
        while(cont != num_aulas) {

            // Se o horário já está ocupado
            while(ExisteElemento(lista, horario))
                horario++;

            // Se sobrou apenas horários na sexta, faz com que a aula vá para a tarde
            if((num_aulas > 1) && (cont == 0) && Grafo->Adj[i].Peso_Vertice > 2) {
                if(horario == 8)
                    horario += 2;
                else if(horario == 9)
                    horario += 1;
            }

            // Insere o novo horário ocupado na lista
            InsereFinalLISTA(lista, horario, Grafo->Adj[i].Codigo_Vertice);
            // Colore o vértice com o horário
            Grafo->Adj[i].Horarios[cont] = horario;
            
            horario += 4;   // Faz com que haja um intervalo de 48h entre aulas

            // Se não é cabível ter um intervalo de 48h, faz um intervalo de 24h
            if(horario >= 10 && cont > 0)
                horario -= 2;
            cont++;
        }
        imprime_passos(Grafo, i);
        horario = 0;
        cont = 0;
    }
    imprime_alocacao_final(Grafo, lista, semestre);
    LiberaLISTA(lista);
}

/**
 *  Função responsável por imprimir a alocação final em um formato de calendário
 *  @param Grafo grafo sobre o qual será operado
 *  @param com_sem_cor inteiro que define se será criado e operado o arquivo colorido ou o sem cor
 */
void cria_dot(TipoGrafo *Grafo, int com_sem_cor) {
    char cores[5][7] = {"red", "blue", "green", "purple", "yellow"};    // Cada cor representa um dos três caminhos críticos
    int semestre = 0, cont;
    FILE *arq;

    if(com_sem_cor == 0)    // Se for pedido sem cor
        arq = fopen("grafoInicial.dot", "w");
    else                    // Se for pedido com cor
        arq = fopen("grafoColorido.dot", "w");    
    
    if(arq == NULL) {
        printf("Erro ao criar o arquivo\n");
    }

    // Cabeçalho do .dot
    fprintf(arq, "strict graph projeto {\n");
    
    Apontador aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        // Se um vértice não tiver adjacentes, imprimí-lo sozinho
        if(aux == NULL) {
            fprintf(arq, "\t%d;\n", Grafo->Adj[i].Codigo_Vertice);
        }
        else {
            // Imprime os vértices de uma aresta no arquivo
            while(aux != NULL) {
                fprintf(arq, "\t%d -- %d;\n", Grafo->Adj[i].Codigo_Vertice, Grafo->Adj[aux->Id].Codigo_Vertice);
                aux = aux->Prox;
            }
        }
        // Se for pedido com cor
        if(com_sem_cor == 1) {
            // Reseta as cores por semestre
            if(semestre != Grafo->Adj[i].Semestre) {
                cont = 0;
                semestre = Grafo->Adj[i].Semestre;
            }
            // Imprime a cor do vértice de acordo com seu horário
            fprintf(arq, "\t%d [color=%s];\n", Grafo->Adj[i].Codigo_Vertice, cores[cont]);
            cont++;
        }
    }
    fprintf(arq, "}");
    fclose(arq);
}

int main() {
    TipoGrafo Grafo;
    Grafo.NumVertices = 31;
    Grafo.NumArestas = 102;

    cria_grafo_vazio(&Grafo);

    monta_grafo(&Grafo);

    cria_dot(&Grafo, 0);

    algoritmo_guloso(&Grafo);

    cria_dot(&Grafo, 1);

    libera_grafo(&Grafo);

    return 0;
}