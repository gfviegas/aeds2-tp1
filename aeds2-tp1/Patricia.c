//
//  Patricia.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 19/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "Patricia.h"

short isExternal(PatriciaNodePointer p) {
    return (p->type == External);
}

PatriciaNodePointer createInternalNodePatricia(int i, PatriciaNodePointer *left, PatriciaNodePointer *right, char compare) {
    PatriciaNodePointer p;
    p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    p->type = Internal;
    p->Node.InternNode.left = *left;
    p->Node.InternNode.right = *right;
    p->Node.InternNode.index = i;
    p->Node.InternNode.compare = compare;
    return p;
}

PatriciaNodePointer createExternalNodePatricia(String k, PatriciaNodePointer *p) {
    *p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    (*p)->type = External;
    strcpy((*p)->Node.word, k);
    return *p;
}

int searchPatricia(String word, PatriciaNodePointer t, int *comparisons, int *height) {
    (*height)++;
    if (isExternal(t)) {
        return (strcmp(word, t->Node.word) == 0) ? 1 : 0;
    }

    if (strlen(word) < t->Node.InternNode.index) {
        (*comparisons)++;
        return searchPatricia(word, t->Node.InternNode.left, comparisons, height);
    } else if (word[t->Node.InternNode.index] < t->Node.InternNode.compare) {
        *comparisons += 2;
        return searchPatricia(word, t->Node.InternNode.left, comparisons, height);
    } else {
        *comparisons += 3;
        return searchPatricia(word, t->Node.InternNode.right, comparisons, height);
    }
}

PatriciaNodePointer PesquisaNoInt(PatriciaNodePointer t, int index, char compara) {
    if (isExternal(t)) {
        return NULL;
    }
    
    if (index == t->Node.InternNode.index && compara == t->Node.InternNode.compare) return t;
    if (index < t->Node.InternNode.index || compara < t->Node.InternNode.compare) return PesquisaNoInt(t->Node.InternNode.left, index, compara);
    if (index < t->Node.InternNode.index || compara < t->Node.InternNode.compare) return PesquisaNoInt(t->Node.InternNode.right, index, compara);
    
    return NULL;
}

PatriciaNodePointer InsereEntre(String word, PatriciaNodePointer *tree, int index, char differentChar) {
    PatriciaNodePointer novoNoExt = NULL;
    PatriciaNodePointer noInterno = NULL;

    noInterno = PesquisaNoInt(*tree, index, differentChar);

    if (isExternal(*tree)) {
        createExternalNodePatricia(word, &novoNoExt);
        
        if (strcmp((*tree)->Node.word, word) < 0) {
            return (createInternalNodePatricia(index, tree, &novoNoExt, differentChar));
        } else if (strcmp((*tree)->Node.word, word) > 0) {
            return (createInternalNodePatricia(index, &novoNoExt, tree, differentChar));
        }
            
        return NULL;
    } else if (index < (*tree)->Node.InternNode.index) {
        //        printf("CHAMOU CRIA NO INTERNO EM %s. -> %d / %d || %c \ %c \n", word, index, (*tree)->Node.InternNode.index, word[index], differentChar);
        createExternalNodePatricia(word, &novoNoExt);
        
        if (word[index] < differentChar) {
            return (createInternalNodePatricia(index, &novoNoExt, tree, differentChar));
        } else {
            return (createInternalNodePatricia(index, tree, &novoNoExt, differentChar));
        }
    } else {
        int indexChanged = (*tree)->Node.InternNode.index;
        // printf("CHAMADA RECURSIVA PRA PALAVRA %s. Difere em %d / %c \n", word, indexChanged, differentChar);
        
        if (word[indexChanged] < (*tree)->Node.InternNode.compare) {
            (*tree)->Node.InternNode.left = InsereEntre(word, &(*tree)->Node.InternNode.left, index, differentChar);
        } else {
            (*tree)->Node.InternNode.right = InsereEntre(word, &(*tree)->Node.InternNode.right, index, differentChar);
        }
        
        return (*tree);
    }
}

PatriciaNodePointer Insere(String k, PatriciaNodePointer *t)
{
    if (*t == NULL)
        return (createExternalNodePatricia(k, t));
    else
    {
        PatriciaNodePointer p = *t;
        int i;
        int ultimoIndex = 0;

        while (!isExternal(p))
        {
            ultimoIndex = p->Node.InternNode.index;

            if (k[p->Node.InternNode.index] < p->Node.InternNode.compare)
                p = p->Node.InternNode.left;
            else if (k[p->Node.InternNode.index] >= p->Node.InternNode.compare)
                p = p->Node.InternNode.right;
            else
                p = p->Node.InternNode.left;
        }

        if (strcmp(p->Node.word, k) == 0) {
            printf("Erro; chave ja na arvore \n");
            return (*t);
        } else {
            /**
             * Trecho da função baseado no trio - Vitor Luís, Lucas Duarte e Vinícius Gabriel
             * Copyright © 2018 UFV Florestal. All rights reserved.
             */
            char charDif;
            // verifica qual palavra é a menor
            int lowerSize = (strlen(k) < strlen(p->Node.word)) ? strlen(k) : strlen(p->Node.word);

            for (i = 0; i <= lowerSize; i++) {
                if (k[i] != p->Node.word[i]) {
                    if (k[i] < p->Node.word[i]) {
                        charDif = p->Node.word[i];
                        break;
                    } else {
                        charDif = k[i];
                        break;
                    }
                }
            }

            //            printf("\t %s. \n\n", k);
            return InsereEntre(k, t, i, charDif);
        }
    }
}

int heightPatricia(PatriciaNodePointer t)
{
    if (t == NULL)
        return 0;
    else
    {
        int he, hd;
        if (t->type == Internal)
        {
            he = heightPatricia(t->Node.InternNode.left);
            hd = heightPatricia(t->Node.InternNode.right);
        }

        if (he < hd)
            return hd + 1;
        else
            return he + 1;
    }
}

void nodeCountPatricia(PatriciaNodePointer t, int *internos, int *externos)
{
    if (t != NULL)
    {
        if (t->type == Internal)
        {
            nodeCountPatricia(t->Node.InternNode.left, internos, externos);
            nodeCountPatricia(t->Node.InternNode.right, internos, externos);
            (*internos)++;
        }
        else
            (*externos)++;
    }
}

int nodeAmmountPatricia(PatriciaNodePointer treePatricia, PatriciaNodeType tipo)
{
    int internos = 0, externos = 0;
    nodeCountPatricia(treePatricia, &internos, &externos);
    return (tipo == External) ? externos : internos;
}

void printPatricia(PatriciaNodePointer t)
{
    if (t != NULL)
    {
        if (t->type == Internal)
            printPatricia(t->Node.InternNode.left);
        if (t->type == External)
            printf("%s\n", t->Node.word);
        if (t->type == Internal)
            printPatricia(t->Node.InternNode.right);
    }
}

void statsPatricia(PatriciaNodePointer t) {
    printf("\t *** Dados da Arvore Patricia: *** \n");
    printf("Numero de nos internos Patricia: %d\n", nodeAmmountPatricia(t, Internal));
    printf("Numero de nos externos Patricia: %d\n", nodeAmmountPatricia(t, External));
    printf("Altura da Patricia: %d\n\n", heightPatricia(t));
    printf("\t ********* \n");
}
