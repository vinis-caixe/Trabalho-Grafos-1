/*
Trabalho 2 de Teoria e Aplicação de Grafos
Pedro Vitor Valença Mizuno - 17/0043665
Vinícius Caixeta de Souza - 18/0132199
*/

// Parte do código de montagem do dígrafo utilizado veio do link fornecido pelo professor: http://www2.dcc.ufmg.br/livros/algoritmos-edicao2/cap7/codigo/c/7.4a7.5e7.8-grafolistaap.c


#include "fila.h"
#include "lista.h"
#include <string.h>

/*Função responsável por criar os vértices do dígrafo e armazenar informações deles*/
void cria_lista_vazia(TipoLista *Lista, char codigo[], int peso, int id, char nome[]) {
    Lista->Primeiro = (Apontador) malloc (sizeof(Celula));
    Lista->Ultimo = Lista->Primeiro;
    strcpy(Lista->Codigo_Vertice, codigo);    // Armazenamos o código da disciplina
    Lista->Peso_Vertice = peso;
    Lista->Id_Vertice = id;
    strcpy(Lista->Nome_Vertice, nome);  // Armazenamos o nome da disciplina
    Lista->Primeiro->Prox = NULL;
}

/*Função responsável por criar o grafo, enviando o código, nome e peso da disciplina para identificação*/
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

/*Função responsável por fazer o grafo reverso baseado no original*/
void monta_grafo_reverso(TipoGrafo *Grafo, TipoGrafo *Reverso) {
    Apontador aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
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
    for(i = 0; i < Grafo->NumVertices; i++){
        graus_chegada[i] = 0;   // Vetores de 32 espaços armazenando o grau de entrada e saída dos 32 vértices
        graus_saida[i] = 0;
    }

    for(i = 0; i < Grafo->NumVertices; i++) {
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
    for(i = 0; i < Grafo->NumVertices; i++) {
        if(graus_chegada[i] == 0) {
            enfileirar(fila, Grafo->Adj[i]);
            graus_chegada[i] = -1;  // Marca como já enfileirado
        }
    }

    Apontador aux;

    while(!ehVaziaFILA(fila)){  // Se a fila não for vazia
        TipoLista vertice_removido = primeiroFILA(fila);
        desenfileirar(fila);
        printf("%s\t%s\n", vertice_removido.Codigo_Vertice, Grafo->Adj[vertice_removido.Id_Vertice].Nome_Vertice);  // Remove o primeiro da fila e printa seu código
        contador++;
        for(i = 0; i < Grafo->NumVertices; i++) {
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

    if(contador != Grafo->NumVertices)
        printf("Nao eh possivel ter uma ordem topologica\n");
    
    liberaFILA(fila);
}

/*Função responsável por encontrar os 3 maiores caminhos críticos com todos os vértices diferentes.
tres_CC armazena os ids do vetores que compõem os 3 maiores caminhos críticos.
tres_PC armazena os pesos totais dos 3 maiores caminhos críticos*/
void tres_caminhos_criticos(LISTA **caminho_critico, int peso_critico, int tres_PC[], int tres_CC[3][6]) {
    int vertices_CC[18], k, repete = -1, i, menor_PC = 99, menor_i;
    for(i = 0; i < 3; i++) {
        for(int j = 0; j < 6; j++) {
            vertices_CC[6*i + j] = tres_CC[i][j];   // Armazena a matriz em um vetor
        }
    }
    for(i = 0; i < 18; i++) {
        k = 0;
        while(PosicaoLISTA(caminho_critico, k) != -1) {
            if(vertices_CC[i] == PosicaoLISTA(caminho_critico, k)) {
                repete = i; // Armazena em repete a posição do vértice repetido, se houver
            }
            k++;
        }
    }
    if(repete == -1) {  // Se não há repetição
        for(i = 0; i < 3; i++) {
            if(menor_PC > tres_PC[i]) {
                menor_PC = tres_PC[i];  // Encontra o menor peso dos 3 caminhos críticos
                menor_i = i;
            }
        }
        for(i = 0; i < 6; i++) {
            if(PosicaoLISTA(caminho_critico, i) != -1) {    // Atualiza no vetor o novo caminho crítico
                vertices_CC[6*menor_i + i] = PosicaoLISTA(caminho_critico, i);
            } else
                vertices_CC[6*menor_i + i] = 0; // Coloca 0 se o caminho crítico já acabou
        }
        tres_PC[menor_i] = peso_critico;    // Atualiza o peso do novo caminho crítico
    } else {    // Se há repetição
        if(tres_PC[repete/6] < peso_critico) { // Compara se o peso do caminho crítico na matriz é menor que o peso do caminho crítico que estamos analisando agora
            tres_PC[repete/6] = peso_critico;
            for(i = 0; i < 6; i++) {
                if(PosicaoLISTA(caminho_critico, i) != -1) {    // Atualiza no vetor o novo caminho crítico
                    vertices_CC[(repete-(repete%6)) + i] = PosicaoLISTA(caminho_critico, i);
                }
                else
                    vertices_CC[(repete-(repete%6)) + i] = 0;   // Coloca 0 se o caminho crítico já acabou
            }
        }
    }
    for(i = 0; i < 3; i++) {    // Reenvia para a matriz os novos valores de vetor
        for(int j = 0; j < 6; j++) {
            tres_CC[i][j] = vertices_CC[6*i + j];
        }
    }
}

/*Função que realiza chamadas recursivas para encontrar os caminhos criticos a partir de um vértice terminal*/
void recursao_backflow(TipoGrafo *Reverso, TipoLista Vertice, int peso_critico, int peso_local, LISTA **caminho_critico, int tres_PC[], int tres_CC[3][6]) {
    Apontador aux;
    if(Vertice.Primeiro->Prox == NULL && peso_local > peso_critico) {   // Se for um vértice inicial e for o caminho crítico com maior peso desse vértice terminal
        peso_critico = peso_local;
        tres_caminhos_criticos(caminho_critico, peso_critico, tres_PC, tres_CC);    // Atualiza a matriz dos 3 maiores caminhos críticos com vetores diferentes
    } else {
        aux = Vertice.Primeiro->Prox;
        while(aux != NULL) {    // Enquanto houver adjacentes
            peso_local += aux->Peso;    // Incrementa o peso do caminho pelo peso do vértice atual
            InsereFinalLISTA(caminho_critico, aux->Id); // Insere o id do vértice na lista do caminho crítico
            recursao_backflow(Reverso, Reverso->Adj[aux->Id], peso_critico, peso_local, caminho_critico, tres_PC, tres_CC);
            aux = aux->Prox;
            peso_local -= Vertice.Peso_Vertice; // Decrementa o peso do caminho
            RemoveFinalLISTA(caminho_critico);  // Remove da lista o id do vértice
        }
    }
    peso_local -= Vertice.Peso_Vertice;
}

/*Função baseada no algoritmo backflow para encontrar caminhos críticos*/
void algoritmo_backflow(TipoGrafo *Grafo, TipoGrafo *Reverso, int graus_saida[], int tres_PC[], int tres_CC[3][6]) {
    int peso_critico = 0, peso_local = 0;
    LISTA **caminho_critico;    // Cria uma lista para armazenar os vértices do caminho crítico
    caminho_critico = CriaIniciaLISTA();
    for(int i = 0; i < Grafo->NumVertices; i++) {
        if(graus_saida[i] == 0) {   // Se for um dos vértices finais (grau de saída 0)
            peso_local += Reverso->Adj[i].Peso_Vertice; // Incrementa o peso
            InsereFinalLISTA(caminho_critico, Reverso->Adj[i].Id_Vertice);
            recursao_backflow(Reverso, Reverso->Adj[i], peso_critico, peso_local, caminho_critico, tres_PC, tres_CC);
            RemoveFinalLISTA(caminho_critico);
        }
        peso_local = 0;
        peso_critico = 0;
    }

    LiberaLISTA(caminho_critico);
}

/*Função responsável por gerar o arquivo dot */
void cria_dot(TipoGrafo *Grafo, int tres_CC[3][6]) {
    char cores[3][6] = {"red", "blue", "green"};    // Cada cor representa um dos três caminhos críticos
    int flag_cor = 0;
    FILE *arq = fopen("grafo.dot", "w");
    if(arq == NULL) {
        printf("Erro ao criar o arquivo\n");
    }

    fprintf(arq, "digraph projeto {\n");
    
    Apontador aux;
    for(int i = 0; i < Grafo->NumVertices; i++) {
        aux = Grafo->Adj[i].Primeiro->Prox;
        if(aux == NULL) {
            fprintf(arq, "\t%s;\n", Grafo->Adj[i].Codigo_Vertice);  // Se um vértice não ter adjacentes imprimí-lo sozinho
        }
        else {
            while(aux != NULL) {
                flag_cor = 0;
                fprintf(arq, "\t%s -> %s", Grafo->Adj[i].Codigo_Vertice, aux->Codigo);   // Imprime os vértices de uma aresta no arquivo
                for(int j = 0; j < 3; j++){     // j representa um dos três possíveis caminhos críticos
                    for(int k = 0; k < 5; k++){
                        if(aux->Id == tres_CC[j][k] && Grafo->Adj[i].Id_Vertice == tres_CC[j][k+1]){    // Se um vértice e seu adjacente estiverem juntos em um dos
                            fprintf(arq, " [color=%s];\n", cores[j]);                                   // três caminhos críticos, determinar uma cor para sua respectiva
                            flag_cor = 1;                                                               // aresta no arquivo
                        }                                                           
                        
                    }
                }
                if(flag_cor == 0)
                    fprintf(arq, ";\n");
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
    
    int graus_chegada[Grafo.NumVertices], graus_saida[Grafo.NumVertices];

    cria_grafo_vazio(&Grafo);

    monta_grafo(&Grafo);

    printf("\n\n--------BACHARELADO EM CIENCIA DA COMPUTACAO--------\n\n\n------CURSOS E SEUS CODIGOS------\n\n");

    for(int i = 0; i < Grafo.NumVertices; i++){
        printf("CURSO: %s\nCODIGO: %s\n\n", Grafo.Adj[i].Nome_Vertice, Grafo.Adj[i].Codigo_Vertice);
    }

    printf("\n------DAG------\n\n");
    imprime_grafo(&Grafo);

    encontra_grau(&Grafo, graus_chegada, graus_saida);

    printf("\n------ORDENACAO TOPOLOGICA------\n\n");
    algoritmo_Kahn(&Grafo, graus_chegada);

    encontra_grau(&Grafo, graus_chegada, graus_saida);

    // O grafo reverso foi criado para ter uma maior facilidade
    // ao acessar os adjacentes por chegada de um dado vértice
    // durante a execução do algoritmo backflow
    TipoGrafo Grafo_Reverso;
    Grafo_Reverso.NumVertices = Grafo.NumVertices;
    Grafo_Reverso.NumArestas = Grafo.NumArestas;
    
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
