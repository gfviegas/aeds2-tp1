//
//  main.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 10/04/18.
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
    printf("|| ||\t NULL 1.0\n");
    printf("|| ||\t Trabalho Prático 1 de \"Algoritmos e Estruturas de Dados\" II \n");
    printf("|| ||\t Maio de 2018 - UFV Campus Florestal\n");
    printf("|| ||\t Bruno Marra (3029), Gustavo Viegas (3026) e Heitor Passeado (3055)\n");
    printf("|| ||\n");
    printf("\nO programa irá pedir pra que você digite um código após cada operação executada. Basta digitar o código requisitado pra a operação ser executada. \n\n");
}

/**
 Imprime instruções de códigos a serem inseridos para o programa executar
 @return codigo da operação escolhida pelo usuário
 */
void imprimeInstrucoes () {
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
 * @function lerOperacao
 * @param  dicionario          Ponteiro do tipo Dicionario que será manipulado
 * @return                     Inteiro representando se o programa deve continuar executando (1) ou não (0)
 */
int lerOperacao (TSTNodePointer *tstRoot, PatriciaNodePointer *patriciaRoot) {
    int codigo, retorno = 1;
    char nome[150];

    imprimeInstrucoes();

    printf("\nInsira o código da operação que deseja executar: ");
    scanf("%d", &codigo);

    switch (codigo) {
        case 0:
            retorno = 0;
            break;
        case 1:
            printf("Processando texto 1... \n");
            strcpy(nome, "./texto1.txt");
            leArquivo(nome, *tstRoot, *patriciaRoot);
            break;
        case 2:
            printf("Processando texto 2... \n");
            strcpy(nome, "./texto2.txt");
            leArquivo(nome, *tstRoot, *patriciaRoot);
            break;
        case 3:
             printf("Processando texto 3... \n");
            strcpy(nome, "./texto3.txt");
            leArquivo(nome, *tstRoot, *patriciaRoot);
            break;
        case 4:
            printTST(*tstRoot);
            break;
        case 5:
            imprimePatricia(*patriciaRoot);
            break;
        case 6:
            dadosTST(*tstRoot);
            break;
        case 7:
            dadosPatricia(*patriciaRoot);
            break;
        default:
            printf("Código inválido!! \n");
            lerOperacao(tstRoot, patriciaRoot);
            break;
    }

    return retorno;
}

int main()
{
    TSTNodePointer root = NULL;
    PatriciaNodePointer patRoot = NULL;

    char nome[64];
    strcpy(nome, "./dicionario.txt");
    alimentaDicionario(nome, &root, &patRoot);

    while (lerOperacao(&root, &patRoot) == 1) {
        printf("\n\n Operação executada! \n\n");
    }

    printf("\n\n Execução Interrompida! (usuário inseriu o código 0).\n");

    return 0;
}

//int main(int argc, char *argv[])
//{ PatriciaNodePointer a = NULL;
//    String c;
//    int  i, j, k, n;
//    int  min = 32, max = 126;
//    String vetor[95];
//    /* Gera uma permutacao aleatoria de chaves dos caracteres ASCII 32 a  126 */
//    struct timeval semente;
//    gettimeofday(&semente,NULL);
//    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
//    for (i = min; i <= max; i++)
//    vetor[i - 32] = i;
//    for (i = min; i <= max; i++)
//    { k = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
//        j = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
//        n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n;
//    }
//    /* Insere cada chave na arvore */
//    for (i = min; i <= max; i++)
//    { c = vetor[i - 32]; printf("Inserindo chave: %c\n", c);
//        a = Insere(c, &a);
//    }
//    /* Gera outra permutacao aleatoria de chaves */
//    for (i = min; i <= max; i++)
//    { k = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
//        j = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
//        n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n;
//    }
//    /* Pesquisa cada chave na arvore */
//    for (i = min; i <= max; i++)
//    { c = vetor[i - 32]; printf("Pesquisando chave: %c\n", c);
//        Pesquisa(c, a);
//    }
//    return 0;
//}
