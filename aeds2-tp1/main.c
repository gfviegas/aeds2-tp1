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

int main()
{
    TSTNodePointer root = NULL;
    PatriciaNodePointer patRoot = NULL;

    char nome[64];
    strcpy(nome, "./dicionario.txt");
    alimentaDicionario(nome, &root, &patRoot);
    printf("n de nos: %d\n", nodeAmountTST(root));
    printf("Altura da TST: %d\n", greaterWordTST(root));
    printf("Altura da Patricia: %d\n\n", alturaPatricia(patRoot));

    printf("TEXTO ONE ---------- \n");
    strcpy(nome, "./texto1.txt");
    leArquivo(nome, root, patRoot);

    printf("TEXTO TWO ---------- \n");
    strcpy(nome, "./texto2.txt");
    leArquivo(nome, root, patRoot);

    printf("TEXTO THREE ---------- \n");
    strcpy(nome, "./texto3.txt");
    leArquivo(nome, root, patRoot);

    //printTST(root);
    imprimePatricia(patRoot);

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
