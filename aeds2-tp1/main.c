//
//  main.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 10/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include <stdio.h>
#include "TST.h"
#include "leitura.h"
#include "leitura.c"
#include "string.h"

int main(int argc, const char * argv[]) {
    TSTNodePointer root = NULL;
    char nome[64];
    strcpy(nome, "./dicionario.txt");
    alimentaDicionario(nome, &root);
    printf("n de nos: %d\n", nodeAmountTST(root));

    printf("TEXTO ONE ---------- \n");
    strcpy(nome, "./texto1.txt");
    leArquivo(nome, root);

    printf("TEXTO TWO ---------- \n");
    strcpy(nome, "./texto2.txt");
    leArquivo(nome, root);

    return 0;
}
