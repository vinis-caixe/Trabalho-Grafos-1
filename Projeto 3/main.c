/*
Trabalho 3 de Teoria e Aplicação de Grafos
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
    int Id_Adjacente;
    Apontador Prox;
};
typedef struct Struct_Celula Celula;

/* Estrutura da lista */
typedef struct TipoLista {
    int Id;
    int Habilitacao;
    int Segunda_Habilitacao;
    int Livre;
    Apontador Primeiro, Ultimo;
} TipoLista;

/* Estrutura do grafo*/
typedef struct TipoGrafo {
    TipoLista Adj[151];
    int NumVertices;
    int NumArestas;
} TipoGrafo;

/**
 *  Função responsável por criar a lista de adjacência
 *  @param Lista Lista de adjacência
 *  @param habilitacao1 habilitacao do professor ou a primeira habilitacao pedida da escola
 *  @param habilitacao2 segunda habilitacao pedida da escola ou 0
 *  @param id identificação do professor ou escola
 *  @param livre variável que verifica se um professor está procurando uma vaga ou se uma escola tem vaga
 */
void cria_lista_vazia(TipoLista *Lista, int habilitacao1, int habilitacao2, int id, int livre) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Id = id;
    Lista->Habilitacao = habilitacao1;
    Lista->Segunda_Habilitacao = habilitacao2;
    Lista->Livre = livre;
    Lista->Primeiro->Prox = NULL;
}

/**
 *  Função responsável por criar o grafo vazio
 *  @param Grafo o grafo utilizado no trabalho
 *  @param habilitacoes[] vetor contendo a habilitações de professores e escolas
 */
void cria_grafo_vazio(TipoGrafo *Grafo, int habilitacoes[]) {
    int cont_hab_dupla = 0;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        if(habilitacoes[i+cont_hab_dupla] < 10) // Se for um professor
            cria_lista_vazia(&Grafo->Adj[i], habilitacoes[i+cont_hab_dupla], 0, i+1, 1);
        else {  // Se for uma escola
            cria_lista_vazia(&Grafo->Adj[i], habilitacoes[i+cont_hab_dupla]-10, habilitacoes[i+cont_hab_dupla+1]-10, i+1, 2);
            cont_hab_dupla++;
        }
    }
}

/**
 *  Função responsável por desalocar a memória usada no grafo
 *  @param Grafo o grafo utilizado no trabalho
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
 *  Função responsável por criar as arestas entre os vértices
 *  @param id identificador da elemento adjacente ao vértice atual
 *  @param Lista vértice de onde será criada a aresta
 */
void insere_aresta(int id, TipoLista *Lista) {
    Lista->Ultimo->Prox = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Ultimo->Prox;
    Lista->Ultimo->Id_Adjacente = id;
    Lista->Ultimo->Prox = NULL;
}

/**
 *  Função responsável por ler o arquivo e armazenar as habilitações dos professores e escolas 
 *  @param habilitacoes[] vetor que ao final da função irá conter as habilitações dos professores e escolas
*/
void leitura_arq_hab(int habilitacoes[]) {
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
            if(id <= 100) {     // Lendo habilitacoes dos professores
                while(linha[i] != ',') // No arquivo de entrada, quando se chega na ',' se sabe que dois espaços na frente haverá a habilitação do professor
                    i++;

                habilitacoes[id-1] = (int)linha[i+2] - 48; // Converte a habilitação do professor em inteiro e o armazen em habilitacoes[]
            } else {
                num_dois_pontos = 0; // Determina se uma escola terá uma ou duas vagas
                while(linha[i] != '\0') {
                    if(linha[i] == ':') { // Se o caractere ':' aparece então dois espaços na frente haverá uma habilitação que a escola requer
                        pos_dois_pontos[num_dois_pontos] = i;
                        num_dois_pontos++;
                    }
                    i++;
                }
                habilitacoes[contador_escola-1] = (int)linha[pos_dois_pontos[0]+2] - 48; // Armazena a primeira vaga na escola
                if(num_dois_pontos == 2) {
                    habilitacoes[contador_escola-1] += 10; // Sinalizar que a habilitação é de escola, no momento em que inserir no grafo se a habilitação for maior que 10 será considerada de escola
                    habilitacoes[contador_escola] = (int)linha[pos_dois_pontos[1]+2] - 48 + 10;
                    contador_escola++;
                }
                contador_escola++;
            }
            id++;
        }
    }

    fclose(arq);
}

/**
 *  Função responsável por ler do arquivo as arestas que farão parte do grafo
 *  @param Grafo grafo que será montado de acordo com as arestas lidas
 */
void leitura_arq_arestas(TipoGrafo *Grafo) {
    char linha[110];
    int i, num_e, escola = 0;    
    FILE *arq = fopen("entradaProj3TAG.txt", "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int id = 1;
    while(!feof(arq)) {
        i = 0;

        fgets(linha, 110, arq);

        // Verifica se está nas linhas sobre professores
        if(linha[0] == '(' && id <= 100) {
            num_e = 0;
            while(linha[i] != '\0') {
                if(linha[i] == 'E') {
                    num_e++;
                    // Transforma os caracteres lidos em números
                    if(linha[i+2] >= '0' && linha[i+2] <= '9'){
                        escola = ((int)linha[i+1] - 48) * 10;
                        escola += (int)linha[i+2] - 48;
                    } else {
                        escola = (int)linha[i+1] - 48;
                    }
                    // Cria a aresta não direcionada
                    insere_aresta(escola + 100, &Grafo->Adj[id-1]);
                    insere_aresta(id, &Grafo->Adj[escola+99]);
                }
                i++;
            }
            id++;
        }
    }

    fclose(arq);
}

/**
 *  Função que realiza as comparações do algoritmo Gale Shapley
 *  @param Grafo grafo que será utilizado para gerar o emparelhamento
 *  @param combinacoes lista que armazena os emparelhamentos
 *  @param cont posicao do vetor de lista de adjacencias
 */
void comparacoes_gs(TipoGrafo *Grafo, LISTA **combinacoes, int cont) {

    Apontador aux_free;

    int id_escola, hab1, hab2, hab_prof, id_prof_removido1, id_prof_removido2;

    // Id da escola adjacente ao professor
    id_escola = Grafo->Adj[cont].Primeiro->Prox->Id_Adjacente;
    // Habilitações 1 e 2 pedidas pela escolas (a segunda pode ser 0, se a escola não possuir 2 habilitações)
    hab1 = Grafo->Adj[id_escola-1].Habilitacao;
    hab2 = Grafo->Adj[id_escola-1].Segunda_Habilitacao;
    // Habilitação do professor
    hab_prof = Grafo->Adj[cont].Habilitacao;
    // Id dos possíveis professores já associados a escola id_escola (-1 se não existir)
    id_prof_removido1 = ProfessorLISTA(combinacoes, id_escola, 1);
    id_prof_removido2 = ProfessorLISTA(combinacoes, id_escola, 2);

    // Se a escola está livre e a habilitação do professor for maior que alguma das pedidas pela escolas
    if(Grafo->Adj[id_escola-1].Livre > 0 && (hab_prof >= hab1 || (hab_prof >= hab2 && hab2 != 0))) {

        // Se tiver professor já associado a uma escola, a habilitação desse professor ser diferente da primeira pedida
        // E o novo professor tiver a habilitação pedida pela primeira
        if(id_prof_removido1 != -1 && Grafo->Adj[id_prof_removido1 - 1].Habilitacao != hab1 && hab_prof == hab1)
            // Insere o novo professor no início da lista
            InsereInicioLISTA(combinacoes, cont+1, id_escola);
        // Se não, colocamos no final da lista (para ordenar qual professor está pela primeira ou segunda habilitação)
        else
            InsereFinalLISTA(combinacoes, cont+1, id_escola);

        Grafo->Adj[id_escola-1].Livre--; // Escola possui menos uma vaga
        Grafo->Adj[cont].Livre = 0; // Professor não procura mais por vaga

    // Se o professor já associado a uma escola tiver habilitação diferente da primeira pedida
    // E o novo professor tem a habilitação pedida
    } else if(hab_prof >= hab1 && Grafo->Adj[id_prof_removido1 - 1].Habilitacao != hab1){
        TrocaProfessorLISTA(combinacoes, id_escola, id_prof_removido1, cont+1);
        Grafo->Adj[cont].Livre = 0; // Professor não procura mais por vaga
        Grafo->Adj[id_prof_removido1 - 1].Livre = 1; // Professor que foi removido volta a procurar vaga em outra escola
        aux_free = Grafo->Adj[id_prof_removido1 - 1].Primeiro->Prox; // Professor removido remove escola de sua lista de preferências
        Grafo->Adj[id_prof_removido1 - 1].Primeiro->Prox = aux_free->Prox;
        free(aux_free);

    // Se o professor já associado a uma escola tiver habilitação diferente da segunda pedida (se houver)
    // E o novo professor tem a habilitação pedida
    } else if(hab_prof >= hab2 && (id_prof_removido2 != -1) && (Grafo->Adj[id_prof_removido2 - 1].Habilitacao != hab2)) {
        TrocaProfessorLISTA(combinacoes, id_escola, id_prof_removido2, cont+1);
        Grafo->Adj[cont].Livre = 0; // Professor não procura mais por vaga
        Grafo->Adj[id_prof_removido2 - 1].Livre = 1; // Professor que foi removido volta a procurar vaga em outra escola
        aux_free = Grafo->Adj[id_prof_removido2 - 1].Primeiro->Prox; // Professor removido remove escola de sua lista de prefêrencias
        Grafo->Adj[id_prof_removido2 - 1].Primeiro->Prox = aux_free->Prox;
        free(aux_free);

    // Caso não consiga vaga na escola o professor a remove de sua lista de preferência
    } else {
        aux_free = Grafo->Adj[cont].Primeiro->Prox;
        Grafo->Adj[cont].Primeiro->Prox = aux_free->Prox;
        free(aux_free);
    }
}

/**
 *  Função baseada no algoritmo de Gale Shapley para encontrar o emparelhamento estável máximo
 *  @param Grafo grafo que será utilizado para gerar o emparelhamento
 */
void gale_shapley(TipoGrafo *Grafo) {
    // Cria uma lista que armazena os emparelhamentos
    LISTA **combinacoes;
    combinacoes = CriaIniciaLISTA();

    int algum_livre = 1, cont = 0, algum_com_proposta = 1;

    // Enquanto algum professor estiver livre e com propostas
    while(algum_livre == 1 && algum_com_proposta == 1) {

        // Se o professor for livre e tiver propostas
        if(Grafo->Adj[cont].Livre != 0 && Grafo->Adj[cont].Primeiro->Prox != NULL) {
            // Realiza as comparações para o emparelhamento
            comparacoes_gs(Grafo, combinacoes, cont);
        }

        // Se não tiver mais propostas, não é mais considerado livre
        if(Grafo->Adj[cont].Primeiro->Prox == NULL)
            Grafo->Adj[cont].Livre = 0;

        algum_livre = 0;
        algum_com_proposta = 0;

        // Checa se todos estão livres e sem proposta
        for(int i = 0; i < 100; i++) {
            if(Grafo->Adj[i].Livre > 0)
                algum_livre = 1;
            if(Grafo->Adj[i].Primeiro->Prox != NULL)
                algum_com_proposta = 1;
        }

        cont++;
        if(cont == 100)
            cont = 0;
    }

    // Imprime o emparelhamento estável máximo
    ImprimeLISTA(combinacoes);

    LiberaLISTA(combinacoes);
}


int main() {
    int habilitacoes[184];

    // Lê as habilitações no arquivo
    leitura_arq_hab(habilitacoes);

    TipoGrafo Grafo;
    Grafo.NumVertices = 150;
    Grafo.NumArestas = 382;

    cria_grafo_vazio(&Grafo, habilitacoes);

    // Lê e monta as arestas do grafo
    leitura_arq_arestas(&Grafo);

    printf("\n-----EMPARELHAMENTO ESTAVEL MAXIMO-----\n\n");

    gale_shapley(&Grafo);

    libera_grafo(&Grafo);

    return 0;
}