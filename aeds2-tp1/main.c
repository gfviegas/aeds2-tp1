//
//  main.c
//  aeds2-tp1
//
//  Created by  Bruno Marra (3029), Gustavo Viegas (3026) e Heitor Passeado (3055) on 10/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include <stdio.h>
#include "TST.h"
#include "Patricia.h"
#include "file.h"
#include "string.h"

/**
 Imprime um cabeçalho com instruções e descrição do programa
 */
void printHeader () {
    printf("|| ||\n");
    printf("|| ||\t Ultra Blaster TreeDictionarizator Tabajara 1.0\n");
    printf("|| ||\t Trabalho Prático 1 de \"Algoritmos e Estruturas de Dados\" II \n");
    printf("|| ||\t Maio de 2018 - UFV Campus Florestal\n");
    printf("|| ||\t Bruno Marra (3029), Gustavo Viegas (3026) e Heitor Passeado (3055)\n");
    printf("|| ||\n");
    printf("\nO programa irá pedir pra que você digite um código após cada operação executada. Basta digitar o código requisitado pra a operação ser executada. \n\n");
}

/**
 Imprime instruções de códigos a serem inseridos para o programa executar
 */
void printInstructions () {
    printf("Os códigos e operações disponíveis são: \n\n");
    printf("Insira 1 \t->\t Ler texto 1\n");
    printf("Insira 2 \t->\t Ler texto 2\n");
    printf("Insira 3 \t->\t Ler texto 3\n");
    printf("Insira 4 \t->\t Imprimir Dicionário TST\n");
    printf("Insira 5 \t->\t Imprimir Dicionário Patricia\n");
    printf("Insira 6 \t->\t Imprimir dados sobre a TST\n");
    printf("Insira 7 \t->\t Imprimir dados sobre a Patricia\n");
    
    printf("Insira 0 \t->\t Interromper execução\n");
}

/**
 * Lê um código e executa a ação a ela vinculada
 * @function readOperation
 * @return                     Inteiro representando se o programa deve continuar executando (1) ou não (0)
 */
int readOperation (TSTNodePointer *tstRoot, PatriciaNodePointer *patriciaRoot) {
    int code, returnValue = 1;
    char filePath[150];

    printInstructions();

    printf("\nInsira o código da operação que deseja executar: ");
    scanf("%d", &code);

    switch (code) {
        case 0:
            returnValue = 0;
            break;
        case 1:
            printf("Processando texto 1... \n");
            strcpy(filePath, "./texto1.txt");
            readFile(filePath, *tstRoot, *patriciaRoot);
            break;
        case 2:
            printf("Processando texto 2... \n");
            strcpy(filePath, "./texto2.txt");
            readFile(filePath, *tstRoot, *patriciaRoot);
            break;
        case 3:
             printf("Processando texto 3... \n");
            strcpy(filePath, "./texto3.txt");
            readFile(filePath, *tstRoot, *patriciaRoot);
            break;
        case 4:
            printTST(*tstRoot);
            break;
        case 5:
            printPatricia(*patriciaRoot);
            break;
        case 6:
            statsTST(*tstRoot);
            break;
        case 7:
            statsPatricia(*patriciaRoot);
            break;
        default:
            printf("Código inválido!! \n");
            readOperation(tstRoot, patriciaRoot);
            break;
    }

    return returnValue;
}

int main() {
    TSTNodePointer rootTST = NULL;
    PatriciaNodePointer rootPatricia = NULL;

    char filePath[64];
    strcpy(filePath, "./dicionario.txt");
    feedDictionary(filePath, &rootTST, &rootPatricia);

    printHeader();
    while (readOperation(&rootTST, &rootPatricia) == 1) {
        printf("\n\n Operação executada! \n\n");
    }

    printf("\n\n Execução Interrompida! (usuário inseriu o código 0).\n");

    return 0;
}
