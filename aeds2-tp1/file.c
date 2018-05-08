//
//  file.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 05/05/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "file.h"

int alimentaDicionario(char *nomeArquivo, TSTNodePointer *TSTtree, PatriciaNodePointer *Pattree) {
    char palavraAtual[50]; // Armazenar· a palavra atual em cada iteração
    FILE *arquivo = NULL;  // Arquivo TXT lido
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL) {
        printf("O arquivo %s nao existe. Encerrando a execucao. \n", nomeArquivo);
        return 0;
    }

    while (1) {
        fscanf(arquivo, "%s", palavraAtual);
        if (fgetc(arquivo) == EOF)
            break;

        for (int i = 0; i < strlen(palavraAtual); i++)
            palavraAtual[i] = tolower(palavraAtual[i]);

        //insere na TST
        insertTST(TSTtree, palavraAtual);

        //insere na Patricia
        *Pattree = Insere(palavraAtual, Pattree);
    }

    fclose(arquivo);
    return 1;
}

void processarTST(FILE *arquivo, TSTNodePointer TSTtree) {
    int notFound = 0, greaterWordNotFound = 0, greaterWordFound = 0, total = 0;
    int comparacoesSucesso = 0;
    int comparacoesInsucesso = 0;
    int comparacoes;
    
    int maiorAlturaSucesso = 0;
    int maiorAlturaInsucesso = 0;
    int altura;

    char palavraAtual[MAX_SIZE], wordFound[MAX_SIZE], wordNotFound[MAX_SIZE];

    printf("|||| ARVORE TST ||||\n\n");
    while (1) {
        comparacoes = 0;
        altura = 0;

        fscanf(arquivo, "%s", palavraAtual);
        if (fgetc(arquivo) == EOF) break;

        for (int i = 0; i < strlen(palavraAtual); i++)
            palavraAtual[i] = tolower(palavraAtual[i]);

        if (!searchTST(TSTtree, palavraAtual, &comparacoes, &altura)) {
            printf("-- Palavra %s nao foi encontrada --\n", palavraAtual);

            if (altura > maiorAlturaInsucesso) {
                strcpy(wordNotFound, palavraAtual);
                maiorAlturaInsucesso = altura;
            }
            notFound++;
            comparacoesInsucesso += comparacoes;
        } else {
            if (altura > maiorAlturaSucesso) {
                strcpy(wordFound, palavraAtual);
                maiorAlturaSucesso = altura;
            }

            comparacoesSucesso += comparacoes;
        }
        total++;
    }

    printf("Total de palavras no texto: %d \n", total);
    printf("Nao foram encontradas %d palavras \n", notFound);
    if (maiorAlturaSucesso)
        printf("Altura da maior palavra procurada encontrada: %d - %s \n", maiorAlturaSucesso, wordFound);
    if (maiorAlturaInsucesso)
        printf("Altura da maior palavra procurada e nao encontrada: %d - %s \n", maiorAlturaInsucesso, wordNotFound);
    printf("Foram feitas %d comparacoes pra pesquisas com sucesso e %d pra pesquisas sem sucesso.\n", comparacoesSucesso, comparacoesInsucesso);
    printf("\n\n");

}

void processarPatricia(FILE *arquivo, PatriciaNodePointer Pattree) {
    int total = 0;
    int notFound = 0;
    
    int comparacoesSucesso = 0;
    int comparacoesInsucesso = 0;
    int comparacoes;
    
    int maiorAlturaSucesso = 0;
    int maiorAlturaInsucesso = 0;
    int altura;
    
    char palavraAtual[MAX_SIZE], wordFound[MAX_SIZE], wordNotFound[MAX_SIZE]; // Armazenar· a palavra atual em cada iteraÁ„o

    printf("|||| ARVORE PATRICIA ||||\n\n");
    while (1) {
        comparacoes = 0;
        altura = 0;
        
        fscanf(arquivo, "%s", palavraAtual);
        if (fgetc(arquivo) == EOF) break;

        for (int i = 0; i < strlen(palavraAtual); i++)
            palavraAtual[i] = tolower(palavraAtual[i]);

        if (!Pesquisa(palavraAtual, Pattree, &comparacoes, &altura)) {
            printf("-- Palavra %s nao foi encontrada --\n", palavraAtual);

            if (altura > maiorAlturaInsucesso) {
                strcpy(wordNotFound, palavraAtual);
                maiorAlturaInsucesso = altura;
            }
            comparacoesInsucesso += comparacoes;
            notFound++;
        } else {
            if (altura > maiorAlturaSucesso) {
                strcpy(wordFound, palavraAtual);
                maiorAlturaSucesso = altura;
            }
            comparacoesSucesso += comparacoes;
        }

        total++;
    }

    printf("Total de palavras no texto: %d \n", total);
    printf("Nao foram encontradas %d palavras \n", notFound);
    if (maiorAlturaSucesso)
        printf("Altura da maior palavra procurada encontrada: %d - %s \n", maiorAlturaSucesso, wordFound);
    if (maiorAlturaInsucesso)
        printf("Altura da maior palavra procurada e nao encontrada: %d - %s \n", maiorAlturaInsucesso, wordNotFound);
    printf("Foram feitas %d comparacoes pra pesquisas com sucesso e %d pra pesquisas sem sucesso.\n", comparacoesSucesso, comparacoesInsucesso);
    printf("\n\n");
}

int leArquivo(char *nomeArquivo, TSTNodePointer TSTtree, PatriciaNodePointer Pattree) {
    FILE *arquivo = NULL;                                                     // Arquivo TXT lido
    arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        printf("O arquivo %s nao existe. Encerrando a execucao. \n", nomeArquivo);
        return 0;
    }
    
    processarTST(arquivo, TSTtree);
    arquivo = fopen(nomeArquivo, "r");
    processarPatricia(arquivo, Pattree);
    
    fclose(arquivo);
    return 1;
}
