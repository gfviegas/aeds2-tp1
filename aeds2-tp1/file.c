//
//  file.c
//  aeds2-tp1
//
//  Created by  Bruno Marra (3029), Gustavo Viegas (3026) e Heitor Passeado (3055) on 10/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "file.h"

// Alimenta o dicionário, lendo o arquivo e inserindo seus valores nas árvores fornecidas
int feedDictionary(char *fileName, TSTNodePointer *treeTST, PatriciaNodePointer *treePatricia) {
    char currentWord[50]; // Armazenar· a palavra atual em cada iteração
    FILE *loadedFile = NULL;  // Arquivo TXT lido
    loadedFile = fopen(fileName, "r");

    if (loadedFile == NULL) {
        printf("O arquivo %s nao existe. Encerrando a execucao. \n", fileName);
        return 0;
    }

    while (1) {
        fscanf(loadedFile, "%s", currentWord);
        if (fgetc(loadedFile) == EOF)
            break;

        for (int i = 0; i < strlen(currentWord); i++)
            currentWord[i] = tolower(currentWord[i]);

        //insere na TST
        insertNodeTST(treeTST, currentWord);

        //insere na Patricia
        *treePatricia = Insere(currentWord, treePatricia);
    }

    fclose(loadedFile);
    return 1;
}

// Processa a árvore TST, comparando cada palavra lida na árvore TST fornecida
void proccessTST(FILE *loadedFile, TSTNodePointer treeTST) {
    int notFound = 0, greaterWordNotFound = 0, greaterWordFound = 0, total = 0;
    int successComparisons = 0;
    int unsuccessComparisons = 0;
    int comparisons;
    
    int successHeight = 0;
    int unsuccessHeight = 0;
    int height;

    char currentWord[MAX_SIZE], wordFound[MAX_SIZE], wordNotFound[MAX_SIZE];

    printf("|||| ARVORE TST ||||\n\n");
    while (1) {
        comparisons = 0;
        height = 0;

        fscanf(loadedFile, "%s", currentWord);
        if (fgetc(loadedFile) == EOF) break;

        for (int i = 0; i < strlen(currentWord); i++)
            currentWord[i] = tolower(currentWord[i]);

        if (!searchTST(treeTST, currentWord, &comparisons, &height)) {
            printf("-- Palavra %s nao foi encontrada --\n", currentWord);

            if (height > unsuccessHeight) {
                strcpy(wordNotFound, currentWord);
                unsuccessHeight = height;
            }
            notFound++;
            unsuccessComparisons += comparisons;
        } else {
            if (height > successHeight) {
                strcpy(wordFound, currentWord);
                successHeight = height;
            }

            successComparisons += comparisons;
        }
        total++;
    }

    printf("Total de palavras no texto: %d \n", total);
    printf("Nao foram encontradas %d palavras \n", notFound);
    if (successHeight)
        printf("Altura da maior palavra procurada encontrada: %d - %s \n", successHeight, wordFound);
    if (unsuccessHeight)
        printf("Altura da maior palavra procurada e nao encontrada: %d - %s \n", unsuccessHeight, wordNotFound);
    printf("Foram feitas %d comparisons pra pesquisas com sucesso e %d pra pesquisas sem sucesso.\n", successComparisons, unsuccessComparisons);
    printf("\n\n");

}

// Processa a árvore Patricia, comparando cada palavra lida na árvore TST fornecida
void proccessPatricia(FILE *loadedFile, PatriciaNodePointer treePatricia) {
    int total = 0;
    int notFound = 0;
    
    int successComparisons = 0;
    int unsuccessComparisons = 0;
    int comparisons;
    
    int successHeight = 0;
    int unsuccessHeight = 0;
    int height;
    
    char currentWord[MAX_SIZE], wordFound[MAX_SIZE], wordNotFound[MAX_SIZE]; // Armazenar a palavra atual em cada iteração

    printf("|||| ARVORE PATRICIA ||||\n\n");
    while (1) {
        comparisons = 0;
        height = 0;
        
        fscanf(loadedFile, "%s", currentWord);
        if (fgetc(loadedFile) == EOF) break;

        for (int i = 0; i < strlen(currentWord); i++)
            currentWord[i] = tolower(currentWord[i]);

        if (!searchPatricia(currentWord, treePatricia, &comparisons, &height)) {
            printf("-- Palavra %s nao foi encontrada --\n", currentWord);

            if (height > unsuccessHeight) {
                strcpy(wordNotFound, currentWord);
                unsuccessHeight = height;
            }
            unsuccessComparisons += comparisons;
            notFound++;
        } else {
            if (height > successHeight) {
                strcpy(wordFound, currentWord);
                successHeight = height;
            }
            successComparisons += comparisons;
        }

        total++;
    }

    printf("Total de palavras no texto: %d \n", total);
    printf("Nao foram encontradas %d palavras \n", notFound);
    if (successHeight)
        printf("Altura da maior palavra procurada encontrada: %d - %s \n", successHeight, wordFound);
    if (unsuccessHeight)
        printf("Altura da maior palavra procurada e nao encontrada: %d - %s \n", unsuccessHeight, wordNotFound);
    printf("Foram feitas %d comparisons pra pesquisas com sucesso e %d pra pesquisas sem sucesso.\n", successComparisons, unsuccessComparisons);
    printf("\n\n");
}

// Lê um arquivo e processa as árvores fornecidas, buscando as palavras no dicionário
int readFile(char *fileName, TSTNodePointer treeTST, PatriciaNodePointer treePatricia) {
    FILE *loadedFile = NULL;                                                     // Arquivo TXT lido
    loadedFile = fopen(fileName, "r");
    
    if (loadedFile == NULL) {
        printf("O loadedFile %s nao existe. Encerrando a execucao. \n", fileName);
        return 0;
    }
    
    proccessTST(loadedFile, treeTST);
    loadedFile = fopen(fileName, "r");
    proccessPatricia(loadedFile, treePatricia);
    
    fclose(loadedFile);
    return 1;
}
