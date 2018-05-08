//
//  Patricia.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 19/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "Patricia.h"

short EExterno(PatriciaNodePointer p) {
    return (p->type == Externo);
}

PatriciaNodePointer CriaNoInt(int i, PatriciaNodePointer *left, PatriciaNodePointer *right, char compare) {
    PatriciaNodePointer p;
    p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    p->type = Interno;
    p->Node.InternNode.left = *left;
    p->Node.InternNode.right = *right;
    p->Node.InternNode.index = i;
    p->Node.InternNode.compare = compare;
    return p;
}

PatriciaNodePointer CriaNoExt(String k, PatriciaNodePointer *p) {
    *p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    (*p)->type = Externo;
    strcpy((*p)->Node.word, k);
    return *p;
}

int Pesquisa(String word, PatriciaNodePointer t, int *comparacoes, int *altura) {
    (*altura)++;
    if (EExterno(t)) {
        return (strcmp(word, t->Node.word) == 0) ? 1 : 0;
    }

    if (strlen(word) < t->Node.InternNode.index) {
        (*comparacoes)++;
        return Pesquisa(word, t->Node.InternNode.left, comparacoes, altura);
    } else if (word[t->Node.InternNode.index] < t->Node.InternNode.compare) {
        *comparacoes += 2;
        return Pesquisa(word, t->Node.InternNode.left, comparacoes, altura);
    } else {
        *comparacoes += 3;
        return Pesquisa(word, t->Node.InternNode.right, comparacoes, altura);
    }
}

PatriciaNodePointer PesquisaNoInt(PatriciaNodePointer t, int index, char compara) {
    if (EExterno(t)) {
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

    if (EExterno(*tree)) {
        CriaNoExt(word, &novoNoExt);
        
        if (strcmp((*tree)->Node.word, word) < 0) {
            return (CriaNoInt(index, tree, &novoNoExt, differentChar));
        } else if (strcmp((*tree)->Node.word, word) > 0) {
            return (CriaNoInt(index, &novoNoExt, tree, differentChar));
        }
            
        return NULL;
    } else if (index < (*tree)->Node.InternNode.index) {
        //        printf("CHAMOU CRIA NO INTERNO EM %s. -> %d / %d || %c \ %c \n", word, index, (*tree)->Node.InternNode.index, word[index], differentChar);
        CriaNoExt(word, &novoNoExt);
        
        if (word[index] < differentChar) {
            return (CriaNoInt(index, &novoNoExt, tree, differentChar));
        } else {
            return (CriaNoInt(index, tree, &novoNoExt, differentChar));
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
        return (CriaNoExt(k, t));
    else
    {
        PatriciaNodePointer p = *t;
        int i;
        int ultimoIndex = 0;

        while (!EExterno(p))
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

int alturaPatricia(PatriciaNodePointer t)
{
    if (t == NULL)
        return 0;
    else
    {
        int he, hd;
        if (t->type == Interno)
        {
            he = alturaPatricia(t->Node.InternNode.left);
            hd = alturaPatricia(t->Node.InternNode.right);
        }

        if (he < hd)
            return hd + 1;
        else
            return he + 1;
    }
}

void numeroNosPatriciaTree(PatriciaNodePointer t, int *internos, int *externos)
{
    if (t != NULL)
    {
        if (t->type == Interno)
        {
            numeroNosPatriciaTree(t->Node.InternNode.left, internos, externos);
            numeroNosPatriciaTree(t->Node.InternNode.right, internos, externos);
            (*internos)++;
        }
        else
            (*externos)++;
    }
}

int numeroNosPatricia(PatriciaNodePointer Pattree, PatriciaNodeType tipo)
{
    int internos = 0, externos = 0;
    numeroNosPatriciaTree(Pattree, &internos, &externos);
    return (tipo == Externo) ? externos : internos;
}

void imprimePatricia(PatriciaNodePointer t)
{
    if (t != NULL)
    {
        if (t->type == Interno)
            imprimePatricia(t->Node.InternNode.left);
        if (t->type == Externo)
            printf("%s\n", t->Node.word);
        if (t->type == Interno)
            imprimePatricia(t->Node.InternNode.right);
    }
}

void dadosPatricia(PatriciaNodePointer t) {
    printf("\t *** Dados da Arvore Patricia: *** \n");
    printf("Numero de nos internos Patricia: %d\n", numeroNosPatricia(t, Interno));
    printf("Numero de nos externos Patricia: %d\n", numeroNosPatricia(t, Externo));
    printf("Altura da Patricia: %d\n\n", alturaPatricia(t));
    printf("\t ********* \n");
}
