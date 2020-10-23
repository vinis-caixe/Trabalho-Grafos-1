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

/* Função responsável por criar a lista de adjacentes */
void cria_lista_vazia(TipoLista *Lista, int habilitacao1, int habilitacao2, int id, int livre) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    Lista->Id = id;
    Lista->Habilitacao = habilitacao1;
    Lista->Segunda_Habilitacao = habilitacao2;
    Lista->Livre = livre;
    Lista->Primeiro->Prox = NULL;
}

/* Função responsável por criar o grafo vazio */
void cria_grafo_vazio(TipoGrafo *Grafo, int habilitacoes[]) {
    int cont_hab_dupla = 0;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        if(habilitacoes[i+cont_hab_dupla] < 10)
            cria_lista_vazia(&Grafo->Adj[i], habilitacoes[i+cont_hab_dupla], 0, i+1, 1);
        else {
            cria_lista_vazia(&Grafo->Adj[i], habilitacoes[i+cont_hab_dupla]-10, habilitacoes[i+cont_hab_dupla+1]-10, i+1, 2);
            cont_hab_dupla++;
        }
    }
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
        printf("%d: %d %d free %d\n", Grafo->Adj[i].Id, Grafo->Adj[i].Habilitacao, Grafo->Adj[i].Segunda_Habilitacao, Grafo->Adj[i].Livre);
        if(Grafo->Adj[i].Primeiro != Grafo->Adj[i].Ultimo) {    // Se não for vazio
            Aux = Grafo->Adj[i].Primeiro->Prox;
            while(Aux != NULL) {
                printf("%d -> ", Aux->Id_Adjacente);
                Aux = Aux->Prox;
            }
        }
        printf("NULL\n\n");
    }
}

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
                    habilitacoes[contador_escola-1] += 10;
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

void leitura_arq_arestas(TipoGrafo *Grafo) {
    char linha[110];
    int i, num_e, pos_e[4], contador_escola = 101, escola = 0;    
    FILE *arq = fopen("entradaProj3TAG.txt", "r");

    if(arq == NULL){
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    int id = 1;
    while(!feof(arq)) {
        for(i = 0; i < 4; i++)
            pos_e[i] = 0;
        i = 0;

        fgets(linha, 110, arq);

        if(linha[0] == '(' && id <= 100) {
            num_e = 0;
            while(linha[i] != '\0') {
                if(linha[i] == 'E') {
                    pos_e[num_e] = i;
                    num_e++;
                    if(linha[i+2] >= '0' && linha[i+2] <= '9'){
                        escola = ((int)linha[i+1] - 48) * 10;
                        escola += (int)linha[i+2] - 48;
                    } else {
                        escola = (int)linha[i+1] - 48;
                    }
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

void gale_shapley(TipoGrafo *Grafo) {
    LISTA **combinacoes;
    combinacoes = CriaIniciaLISTA();
    Apontador aux_free;
    int algum_livre = 1, cont = 0, id_escola, oi = 0, hab1, hab2, hab_prof;

    while(algum_livre == 1/*cont < 100*/) {

        id_escola = Grafo->Adj[cont].Primeiro->Prox->Id_Adjacente;
        hab1 = Grafo->Adj[id_escola-1].Habilitacao;
        hab2 = Grafo->Adj[id_escola-1].Segunda_Habilitacao;
        hab_prof = Grafo->Adj[cont].Habilitacao;
        if(Grafo->Adj[cont].Livre != 0) {
            if(Grafo->Adj[id_escola-1].Livre > 0) {
                InsereFinalLISTA(combinacoes, cont+1, id_escola);
                ImprimeLISTA(combinacoes);
                Grafo->Adj[id_escola-1].Livre--;
                Grafo->Adj[cont].Livre = 0;
            }/* else if(hab_prof == hab1 && Grafo->Adj[ProfessorLISTA(combinacoes, id_escola) - 1].Habilitacao != hab1){
                int id_prof_removido = ProfessorLISTA(combinacoes, id_escola);
                RemoveBuscaLISTA(combinacoes, id_prof_removido, id_escola);
                InsereFinalLISTA(combinacoes, cont+1, id_escola);
                Grafo->Adj[cont].Livre = 0;
                Grafo->Adj[id_prof_removido-1].Livre = 1;
                aux_free = Grafo->Adj[id_prof_removido-1].Primeiro->Prox;
                Grafo->Adj[id_prof_removido-1].Primeiro->Prox = aux_free->Prox;
                free(aux_free);
            }*/ else {            // ESTOU COM A IDEIA DE TALVEZ COLOCAR O ID DOS PROFESSORES CONTRATADOS PROVISORIAMENTE NO VÉRTICE DAS ESCOLAS E VICE-VERSA
                aux_free = Grafo->Adj[cont].Primeiro->Prox;
                Grafo->Adj[cont].Primeiro->Prox = aux_free->Prox;
                free(aux_free);
                if(Grafo->Adj[cont].Primeiro->Prox == NULL)
                    Grafo->Adj[cont].Livre = 0;
            }
        }

        algum_livre = 0;
        for(int i = 0; i < 100; i++) {
            if(Grafo->Adj[i].Livre > 0)
                algum_livre = 1;
        }
        cont++;
        if(cont == 100)
            cont = 0;
    }
    /*
    int professor, escola, algum_livre = 1, algum_com_proposta = 1, i = 0;
    TipoLista aux;
    Apontador aux_free;

    while(algum_livre && algum_com_proposta){
        i = 0;
        while(i < 100) {
            aux = Grafo->Adj[i];
            if(aux.Primeiro != aux.Ultimo && Grafo->Adj[i].Livre == 1) {
                escola = aux.Primeiro->Prox->Id_Adjacente;
                if(Grafo->Adj[escola-1].Livre > 0) {
                    InsereFinalLISTA(combinacoes, i+1, escola);    // Estamos colocando a POSICAO NA LISTA DE ADJ não o id deles de verdade (que é +1)
                    Grafo->Adj[escola-1].Livre--;
                    Grafo->Adj[i].Livre = 0;
                    ImprimeLISTA(combinacoes);
                } else if (aux.Habilitacao == Grafo->Adj[escola-1].Habilitacao && Grafo->Adj[PosicaoLISTA(combinacoes, escola) - 1].Habilitacao != Grafo->Adj[escola-1].Habilitacao) {
                    RemoveBuscaLISTA(combinacoes, Grafo->Adj[PosicaoLISTA(combinacoes, escola) - 1].Id, Grafo->Adj[escola-1].Id);
                    InsereFinalLISTA(combinacoes, aux.Id, Grafo->Adj[escola-1].Id);
                    Grafo->Adj[PosicaoLISTA(combinacoes, escola) - 1].Livre = 1;
                    Grafo->Adj[i].Livre = 0;
                    ImprimeLISTA(combinacoes);
                    // tira da lista o professor menos qualificado e coloca o novo
                } else if (aux.Habilitacao == Grafo->Adj[escola-1].Segunda_Habilitacao && Grafo->Adj[PosicaoLISTA(combinacoes, escola) - 1].Habilitacao != Grafo->Adj[escola-1].Segunda_Habilitacao) { 
                    RemoveBuscaLISTA(combinacoes, Grafo->Adj[PosicaoLISTA(combinacoes, escola) - 1].Id, Grafo->Adj[escola-1].Id);
                    InsereFinalLISTA(combinacoes, aux.Id, Grafo->Adj[escola-1].Id);
                    Grafo->Adj[PosicaoLISTA(combinacoes, escola) - 1].Livre = 1;
                    Grafo->Adj[i].Livre = 0;
                    //ImprimeLISTA(combinacoes);
                    // tira da lista o professor menos qualificado da segunda habilitação e coloca o novo
                } else {
                    aux_free = aux.Primeiro;
                    aux.Primeiro = aux.Primeiro->Prox;
                    free(aux_free);
                    // retira a aresta do grafo (ou a gente pode colocar um ponteiro pra uma posição, como primeiro e ultimo)
                }
            }

            i++;
        }


        algum_livre = 0;
        algum_com_proposta = 0;
        for(int i = 0; i < 100; i++) {
            if(Grafo->Adj[i].Primeiro != Grafo->Adj[i].Ultimo)
                algum_com_proposta = 1;
            if(Grafo->Adj[i].Livre >= 1)
                algum_livre = 1;
        }
    }*/

    LiberaLISTA(combinacoes);
}

int main() {
    int habilitacoes[184];
    leitura_arq_hab(habilitacoes);

    TipoGrafo Grafo;
    Grafo.NumVertices = 150;
    Grafo.NumArestas = 382;

    cria_grafo_vazio(&Grafo, habilitacoes);

    leitura_arq_arestas(&Grafo);

    //imprime_grafo(&Grafo);
    gale_shapley(&Grafo);
    //imprime_grafo(&Grafo);

    libera_grafo(&Grafo);

    return 0;
}