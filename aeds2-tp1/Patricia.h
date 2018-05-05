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
#define D 8   /* depende de String */
#define MAX_SIZE 50

typedef char String[MAX_SIZE]; /* a definir, dependendo da aplicacao */
typedef short StringIndex;
typedef unsigned char TipoDib;
typedef enum {
    Interno, Externo
} PatriciaNodeType;
typedef struct PatriciaNode* PatriciaNodePointer;
typedef struct PatriciaNode {
    PatriciaNodeType type;
    union {
        struct {
            StringIndex index;
            char compare;
            PatriciaNodePointer left, right;
        } InternNode;
        
        String word;
    } Node;
} PatriciaNode;

short EExterno(PatriciaNodePointer p);
PatriciaNodePointer CriaNoInt(int i, PatriciaNodePointer *left,  PatriciaNodePointer *right, char compare);
PatriciaNodePointer CriaNoExt(String k, PatriciaNodePointer *p);
void Pesquisa(String k, PatriciaNodePointer t);
PatriciaNodePointer InsereEntre(String palavra, PatriciaNodePointer *t, int i);
PatriciaNodePointer Insere(String k, PatriciaNodePointer *t);
#endif /* Patricia_h */
