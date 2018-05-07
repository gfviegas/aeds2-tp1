//
//  Patricia.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 19/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "Patricia.h"

short EExterno(PatriciaNodePointer p)
{
    return (p->type == Externo);
}

PatriciaNodePointer CriaNoInt(int i, PatriciaNodePointer *left, PatriciaNodePointer *right, char compare)
{
    PatriciaNodePointer p;
    p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    p->type = Interno;
    p->Node.InternNode.left = *left;
    p->Node.InternNode.right = *right;
    p->Node.InternNode.index = i;
    p->Node.InternNode.compare = compare;
    return p;
}

PatriciaNodePointer CriaNoExt(String k, PatriciaNodePointer *p)
{
    *p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    (*p)->type = Externo;
    strcpy((*p)->Node.word, k);
    return *p;
}

int Pesquisa(String k, PatriciaNodePointer t)
{
    if (EExterno(t))
        return (strcmp(k, t->Node.word) == 0) ? 1 : 0;

    if (k[t->Node.InternNode.index] <= t->Node.InternNode.compare)
        Pesquisa(k, t->Node.InternNode.left);
    else
        Pesquisa(k, t->Node.InternNode.right);
}

PatriciaNodePointer InsereEntre(String palavra, PatriciaNodePointer *t, int i)
{
    PatriciaNodePointer novoNoExt = NULL;
    char caracter;

    if (EExterno(*t) || i < (*t)->Node.InternNode.index)
    {
        CriaNoExt(palavra, &novoNoExt);

        if ((*t)->Node.word[i] <= palavra[i])
        {
            caracter = (*t)->Node.word[i];
            *t = CriaNoInt(i, t, &novoNoExt, caracter);
        }
        else
            *t = CriaNoInt(i, &novoNoExt, t, palavra[i]);

        return novoNoExt;
    }
    else
    {
        if ((*t)->Node.InternNode.compare <= palavra[i])
            (*t)->Node.InternNode.right = InsereEntre(palavra, &(*t)->Node.InternNode.right, i);
        else
            (*t)->Node.InternNode.left = InsereEntre(palavra, &(*t)->Node.InternNode.left, i);

        return (*t);
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

            if (k[p->Node.InternNode.index] <= p->Node.InternNode.compare)
                p = p->Node.InternNode.left;
            else
                p = p->Node.InternNode.right;
        }

        for (i = 0; i < MAX_SIZE; i++)
            if (k[i] != p->Node.word[i])
                return InsereEntre(k, t, i);

        printf("Erro; chave ja na arvore \n");
        return 0;
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
