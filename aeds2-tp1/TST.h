//
//  TST.h
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 17/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef TST_h
#define TST_h

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define MAX_SIZE 50
typedef char TSTValue;
typedef struct TSTNode *TSTNodePointer;

typedef struct TSTNode
{
    TSTValue data;

    // 1 se termina uma palavra no nó
    unsigned isEndOfString : 1;
    TSTNodePointer left, eq, right;
} TSTNode;

int greaterWordTST(TSTNodePointer root);
void greaterWordTSTtree(TSTNodePointer root, char *buffer, int i, int *bigger);
void insertTST(TSTNodePointer *root, char *word);
int searchTST(TSTNodePointer root, char *word);
void printTSTtree(TSTNodePointer root, char *buffer, int depth);
void printTST(TSTNodePointer root);
int max(int a, int b);

int heightTST(TSTNodePointer root);
int nodeAmountTST(TSTNodePointer root);

#endif /* TST_h */
