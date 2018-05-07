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

PatriciaNodePointer InsereEntre(String palavra, PatriciaNodePointer *t, int i, char charDif)
{
    PatriciaNodePointer novoNoExt = NULL;

    if (EExterno(*t))
    {
        CriaNoExt(palavra, &novoNoExt);

        if (strcmp((*t)->Node.word, palavra) < 0)
            return (CriaNoInt(i, t, &novoNoExt, (*t)->Node.word[i]));
        else
            return (CriaNoInt(i, &novoNoExt, t, palavra[i]));
    }

    /**
     * Trecho da função baseado no trio - Vitor Luís, Lucas Duarte e Vinícius Gabriel
     * Copyright © 2018 UFV Florestal. All rights reserved.
     */
    else if (i < (*t)->Node.InternNode.index)
    {
        /* Cria um novo no externo */
        CriaNoExt(palavra, &novoNoExt);
        if (palavra[i] < charDif)
            return (CriaNoInt(i, t, &novoNoExt, charDif));
        else
            return (CriaNoInt(i, &novoNoExt, t, charDif));
    }
    else
    {
        if ((*t)->Node.InternNode.compare <= palavra[(*t)->Node.InternNode.index])
            (*t)->Node.InternNode.right = InsereEntre(palavra, &(*t)->Node.InternNode.right, i, charDif);
        else
            (*t)->Node.InternNode.left = InsereEntre(palavra, &(*t)->Node.InternNode.left, i, charDif);

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

            if (k[p->Node.InternNode.index] < p->Node.InternNode.compare)
                p = p->Node.InternNode.left;
            else if (k[p->Node.InternNode.index] >= p->Node.InternNode.compare)
                p = p->Node.InternNode.right;
            else
                p = p->Node.InternNode.left;
        }

        if (strcmp(p->Node.word, k) == 0)
        {
            printf("Erro; chave ja na arvore \n");
            return (*t);
        }
        else
        {
            /**
             * Trecho da função baseado no trio - Vitor Luís, Lucas Duarte e Vinícius Gabriel
             * Copyright © 2018 UFV Florestal. All rights reserved.
             */
            char charDif;
            // verifica qual palavra é a menor
            int lowerSize = (strlen(k) < strlen(p->Node.word)) ? strlen(k) : strlen(p->Node.word);

            for (i = 0; i <= lowerSize; i++)
            {
                if (k[i] != p->Node.word[i])
                {
                    if (k[i] < p->Node.word[i])
                    {
                        charDif = p->Node.word[i];
                        break;
                    }
                    else
                    {
                        charDif = k[i];
                        break;
                    }
                }
            }

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
