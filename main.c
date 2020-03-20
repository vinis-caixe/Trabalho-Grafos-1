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

int main() {
    int vetores[159][2];
    le_arquivo(vetores);

    for(int i = 0; i < 159; i++) {
        for(int j = 0; j < 2; j++) {
            printf("%d ", vetores[i][j]);
        }
        printf("\n");
    }

    return 0;
}