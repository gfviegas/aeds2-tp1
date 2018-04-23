#include "leitura.h"
#define BUFFERSIZE 255
int alimentaDicionario(char *nomeArquivo, TSTNodePointer *TSTtree) {
    int linhaAtual = 1; // Inteiro que armazena a linha onde a palavra estará
    char buffer[BUFFERSIZE]; // Buffer de uma linha (255 caracteres)
    char palavraAtual[50]; // Armazenará a palavra atual em cada iteração
    FILE *arquivo = NULL; // Arquivo TXT lido
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("O arquivo %s não existe. Encerrando a execução. \n", nomeArquivo);
        return 0;
    }

    while (1) {
        fscanf(arquivo, "%s", palavraAtual);
        if (fgetc(arquivo) == EOF)
            break;

        insertTST(TSTtree, palavraAtual);
    }

    fclose(arquivo);
    return 1;
}

int leArquivo(char *nomeArquivo, TSTNodePointer TSTtree) {
    int cont = 0;
    char palavraAtual[50]; // Armazenará a palavra atual em cada iteração
    FILE *arquivo = NULL; // Arquivo TXT lido
    arquivo = fopen(nomeArquivo, "r");

    int match;


    if (arquivo == NULL) {
        printf("O arquivo %s não existe. Encerrando a execução. \n", nomeArquivo);
        return 0;
    }

    while (1) {
        fscanf(arquivo, "%s", palavraAtual);
        if (fgetc(arquivo) == EOF) break;

        match = searchTST(TSTtree, palavraAtual);
//        printf("Match: %s -> %d \n", palavraAtual, match);
        if (!match) {
            printf("Palavra %s nao foi encontrada \n", palavraAtual);
            cont++;
        }
    }

    printf("Nao foram encontradas %d palavras \n", cont);

    fclose(arquivo);
    return 1;
}
