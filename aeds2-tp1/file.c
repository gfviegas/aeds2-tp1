//
//  file.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 05/05/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "file.h"

int alimentaDicionario(char *nomeArquivo, TSTNodePointer *TSTtree, PatriciaNodePointer *Pattree)
{
    char palavraAtual[50]; // Armazenar· a palavra atual em cada iteraÁ„o
    FILE *arquivo = NULL;  // Arquivo TXT lido
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("O arquivo %s nao existe. Encerrando a execucao. \n", nomeArquivo);
        return 0;
    }

    while (1)
    {
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

int leArquivo(char *nomeArquivo, TSTNodePointer TSTtree, PatriciaNodePointer Pattree)
{
    FILE *arquivo = NULL;                                                     // Arquivo TXT lido
    arquivo = fopen(nomeArquivo, "r");

    if (arquivo == NULL)
    {
        printf("O arquivo %s nao existe. Encerrando a execucao. \n", nomeArquivo);
        return 0;
    }

    processarTST(arquivo, TSTtree);
    arquivo = fopen(nomeArquivo, "r");
    processarPatricia(arquivo, Pattree);

    fclose(arquivo);
    return 1;
}

void processarTST(FILE *arquivo, TSTNodePointer TSTtree) {
    int notFound = 0, greaterWordNotFound = 0, greaterWordFound = 0, total = 0;
    int comparacoesSucesso = 0;
    int comparacoesInsucesso = 0;
    int comparacoes = 0;
    char palavraAtual[MAX_SIZE], wordFound[MAX_SIZE], wordNotFound[MAX_SIZE]; // Armazenar· a palavra atual em cada iteraÁ„o

    printf("|||| ARVORE TST ||||\n\n");
    while (1)
    {
        fscanf(arquivo, "%s", palavraAtual);
        if (fgetc(arquivo) == EOF)
            break;

        for (int i = 0; i < strlen(palavraAtual); i++)
            palavraAtual[i] = tolower(palavraAtual[i]);

        comparacoes = 0;

        if (!searchTST(TSTtree, palavraAtual, &comparacoes))
        {
            if (strlen(palavraAtual) > greaterWordNotFound)
            {
                greaterWordNotFound = strlen(palavraAtual);
                strcpy(wordNotFound, palavraAtual);
            }

            printf("-- Palavra %s nao foi encontrada --\n", palavraAtual);
            notFound++;
            comparacoesSucesso += comparacoes;
        }
        else
        {
            if (strlen(palavraAtual) > greaterWordFound)
            {
                strcpy(wordFound, palavraAtual);
                greaterWordFound = strlen(palavraAtual);
            }

            comparacoesInsucesso += comparacoes;
        }

        printf("Foram feitas %d comparações para pesquisar essa palavra. \n", comparacoes);
        total++;
    }

    printf("Total de palavras no texto: %d \n", total);
    printf("Nao foram encontradas %d palavras \n", notFound);
    if (greaterWordFound)
        printf("Maior palavra procurada encontrada: %d - %s \n", greaterWordFound, wordFound);
    if (greaterWordNotFound)
        printf("Maior palavra procurada e nao encontrada: %d - %s \n", greaterWordNotFound, wordNotFound);
    printf("Foram feitas %d comparacoes pra pesquisas com sucesso e %d pra pesquisas sem sucesso.\n", comparacoesSucesso, comparacoesInsucesso);
    printf("\n\n");

}

void processarPatricia(FILE *arquivo, PatriciaNodePointer Pattree) {
    int notFound = 0, greaterWordNotFound = 0, greaterWordFound = 0, total = 0;
    int comparacoesSucesso = 0;
    int comparacoesInsucesso = 0;
    int comparacoes = 0;
    char palavraAtual[MAX_SIZE], wordFound[MAX_SIZE], wordNotFound[MAX_SIZE]; // Armazenar· a palavra atual em cada iteraÁ„o

    printf("|||| ARVORE PATRICIA ||||\n\n");
    while (1)
    {
        fscanf(arquivo, "%s", palavraAtual);
        if (fgetc(arquivo) == EOF)
            break;

        for (int i = 0; i < strlen(palavraAtual); i++)
            palavraAtual[i] = tolower(palavraAtual[i]);

        if (!Pesquisa(palavraAtual, Pattree, &comparacoes))
        {
            if (strlen(palavraAtual) > greaterWordNotFound)
            {
                greaterWordNotFound = strlen(palavraAtual);
                strcpy(wordNotFound, palavraAtual);
            }

            printf("-- Palavra %s nao foi encontrada --\n", palavraAtual);

            comparacoesSucesso += comparacoes;
            notFound++;
        }
        else
        {
            if (strlen(palavraAtual) > greaterWordFound)
            {
                strcpy(wordFound, palavraAtual);
                greaterWordFound = strlen(palavraAtual);
            }

            comparacoesInsucesso += comparacoes;
        }

        printf("Foram feitas %d comparações para pesquisar essa palavra. \n", comparacoes);
        total++;
    }

    printf("Total de palavras no texto: %d \n", total);
    printf("Nao foram encontradas %d palavras \n", notFound);
    if (greaterWordFound)
        printf("Maior palavra procurada encontrada: %d - %s \n", greaterWordFound, wordFound);
    if (greaterWordNotFound)
        printf("Maior palavra procurada e nao encontrada: %d - %s \n", greaterWordNotFound, wordNotFound);
    printf("Foram feitas %d comparacoes pra pesquisas com sucesso e %d pra pesquisas sem sucesso.\n", comparacoesSucesso, comparacoesInsucesso);
    printf("\n\n");
}