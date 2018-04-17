//
//  main.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 10/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include <stdio.h>
#include "TST.h"

int main(int argc, const char * argv[]) {
    TSTNodePointer root = NULL;
    insertTST(&root,"she");
    insertTST(&root,"sells");
    insertTST(&root,"sea");
    insertTST(&root,"shells");
    insertTST(&root,"by");
    insertTST(&root,"the");
    insertTST(&root,"sea");
    insertTST(&root,"shore");
    insertTST(&root,"are");
    insertTST(&root,"surely");
    printf("Altura: %d \n", heightTST(root));
    printf("Nós: %d \n", nodeAmountTST(root));
    return 0;

    
    return 0;
}
