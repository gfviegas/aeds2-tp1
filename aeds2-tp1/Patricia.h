//
//  Patricia.h
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 19/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef Patricia_h
#define Patricia_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#define D 8 /* depende de String */
#define MAX_SIZE 50

#include "TST.h"
#include "Patricia.h"

typedef char String[MAX_SIZE]; /* a definir, dependendo da aplicacao */
typedef short StringIndex;
typedef enum {
    Internal,
    External
} PatriciaNodeType;
typedef struct PatriciaNode *PatriciaNodePointer;
typedef struct PatriciaNode
{
    PatriciaNodeType type;
    union {
        struct
        {
            StringIndex index;
            char compare;
            PatriciaNodePointer left, right;
        } InternNode;

        String word;
    } Node;
} PatriciaNode;

int heightPatricia(PatriciaNodePointer t);
short isExternal(PatriciaNodePointer p);
PatriciaNodePointer createInternalNodePatricia(int i, PatriciaNodePointer *left, PatriciaNodePointer *right, char compare);
PatriciaNodePointer createExternalNodePatricia(String k, PatriciaNodePointer *p);
int searchPatricia(String k, PatriciaNodePointer t, int *comparisons, int *height);
PatriciaNodePointer InsereEntre(String palavra, PatriciaNodePointer *t, int i, char charDif);
PatriciaNodePointer Insere(String k, PatriciaNodePointer *t);
void nodeCountPatricia(PatriciaNodePointer t, int *internos, int *externos);
int nodeAmmountPatricia(PatriciaNodePointer t, PatriciaNodeType tipo);
void printPatricia(PatriciaNodePointer t);
void statsPatricia(PatriciaNodePointer t);
void proccessTST(FILE *loadedFile, TSTNodePointer treeTST);
void proccessPatricia(FILE *loadedFile, PatriciaNodePointer treePatricia);


#endif /* Patricia_h */
