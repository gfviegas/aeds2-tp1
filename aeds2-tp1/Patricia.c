//
//  Patricia.c
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 19/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#include "Patricia.h"

// Verifica se um certo nó da árvore é externo ou não
short isExternal(PatriciaNodePointer node) {
    return (node->type == External);
}

// Percorre a árvore Patricia a fim de descobrir a sua altura
int heightPatricia(PatriciaNodePointer tree) {
    int leftHeight = 0, rightHeight = 0;

    if (tree == NULL) {
        return 0;
    } else {
        if (!isExternal(tree)) {
            leftHeight = heightPatricia(tree->Node.InternNode.left);
            rightHeight = heightPatricia(tree->Node.InternNode.right);
        }
        
        if (leftHeight < rightHeight)
            return rightHeight + 1;
        else
            return leftHeight + 1;
    }
}

// Cria um novo nó interno na árvore, alocando a memória e apontando os dados passados
PatriciaNodePointer createInternalNodePatricia(PatriciaNodePointer *left, PatriciaNodePointer *right, int index, char compare) {
    PatriciaNodePointer p;
    p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    p->type = Internal;
    p->Node.InternNode.left = *left;
    p->Node.InternNode.right = *right;
    p->Node.InternNode.index = index;
    p->Node.InternNode.compare = compare;
    return p;
}

// Cria um novo nó externo na árvore, alocando a memória e setando os dados passados
PatriciaNodePointer createExternalNodePatricia(String word, PatriciaNodePointer *p) {
    *p = (PatriciaNodePointer)malloc(sizeof(PatriciaNode));
    (*p)->type = External;
    strcpy((*p)->Node.word, word);
    return *p;
}

// Pesquisa uma palavra na árvore, percorrendo recursivamente até encontrar (ou não) a palavra
short searchPatricia(String word, PatriciaNodePointer tree, int *comparisons, int *height) {
    (*height)++;
    if (isExternal(tree)) {
        return (strcmp(word, tree->Node.word) == 0) ? 1 : 0;
    }

    if (strlen(word) < tree->Node.InternNode.index) {
        (*comparisons)++;
        return searchPatricia(word, tree->Node.InternNode.left, comparisons, height);
    } else if (word[tree->Node.InternNode.index] < tree->Node.InternNode.compare) {
        *comparisons += 2;
        return searchPatricia(word, tree->Node.InternNode.left, comparisons, height);
    } else {
        *comparisons += 3;
        return searchPatricia(word, tree->Node.InternNode.right, comparisons, height);
    }
}

// Insere um nó na árvore, criando nós internos, se necessário, para alocar uma nova palavra à árvore
PatriciaNodePointer insertBetweenPatricia(String word, PatriciaNodePointer *tree, int index, char differentChar) {
    PatriciaNodePointer novoNoExt = NULL;

    if (isExternal(*tree)) {
        createExternalNodePatricia(word, &novoNoExt);
        
        if (strcmp((*tree)->Node.word, word) < 0) {
            return (createInternalNodePatricia(tree, &novoNoExt, index, differentChar));
        } else if (strcmp((*tree)->Node.word, word) > 0) {
            return (createInternalNodePatricia(&novoNoExt, tree, index, differentChar));
        }
            
        return NULL;
    } else if (index < (*tree)->Node.InternNode.index) {
        createExternalNodePatricia(word, &novoNoExt);
        
        if (word[index] < differentChar) {
            return (createInternalNodePatricia(&novoNoExt, tree, index, differentChar));
        } else {
            return (createInternalNodePatricia(tree, &novoNoExt, index, differentChar));
        }
    } else {
        int indexChanged = (*tree)->Node.InternNode.index;
        
        if (word[indexChanged] < (*tree)->Node.InternNode.compare) {
            (*tree)->Node.InternNode.left = insertBetweenPatricia(word, &(*tree)->Node.InternNode.left, index, differentChar);
        } else {
            (*tree)->Node.InternNode.right = insertBetweenPatricia(word, &(*tree)->Node.InternNode.right, index, differentChar);
        }
        
        return (*tree);
    }
}

// Chama as funções necessárias e análise de onde difere para inserir uma nova palavra à árvore
PatriciaNodePointer insertPatricia(String word, PatriciaNodePointer *tree) {
    if (*tree == NULL) {
        return (createExternalNodePatricia(word, tree));
    } else {
        PatriciaNodePointer p = *tree;
        int index;
        int lastIndex = 0;

        while (!isExternal(p)) {
            lastIndex = p->Node.InternNode.index;

            if (word[p->Node.InternNode.index] < p->Node.InternNode.compare)
                p = p->Node.InternNode.left;
            else if (word[p->Node.InternNode.index] >= p->Node.InternNode.compare)
                p = p->Node.InternNode.right;
            else
                p = p->Node.InternNode.left;
        }

        if (strcmp(p->Node.word, word) == 0) {
            printf("Erro; chave ja na arvore \n");
            return (*tree);
        } else {
            /**
             * Trecho da função baseado no trio - Vitor Luís, Lucas Duarte e Vinícius Gabriel
             * Copyright © 2018 UFV Florestal. All rights reserved.
             */
            char charDif;
            
            // Verifica qual palavra é a menor
            int lowerSize = (strlen(word) < strlen(p->Node.word)) ? strlen(word) : strlen(p->Node.word);

            for (index = 0; index <= lowerSize; index++) {
                if (word[index] != p->Node.word[index]) {
                    if (word[index] < p->Node.word[index]) {
                        charDif = p->Node.word[index];
                        break;
                    } else {
                        charDif = word[index];
                        break;
                    }
                }
            }

            return insertBetweenPatricia(word, tree, index, charDif);
        }
    }
}

// Registra a quantidade de nós em uma sub-árvore Patrícia, recursivamente
void nodeCountPatricia(PatriciaNodePointer tree, int *internalNodes, int *externalNodes) {
    if (tree != NULL) {
        if (tree->type == Internal)
        {
            nodeCountPatricia(tree->Node.InternNode.left, internalNodes, externalNodes);
            nodeCountPatricia(tree->Node.InternNode.right, internalNodes, externalNodes);
            (*internalNodes)++;
        }
        else
            (*externalNodes)++;
    }
}

// Retorna a quantidade de nós encontrados em uma árvore Patricia, de um determinado tipo
int nodeAmmountPatricia(PatriciaNodePointer tree, PatriciaNodeType nodeType) {
    int internalNodes = 0, externalNodes = 0;
    nodeCountPatricia(tree, &internalNodes, &externalNodes);
    return (nodeType == External) ? externalNodes : internalNodes;
}

// Percorre uma árvore patricia, imprimindo os seus registros
void printPatricia(PatriciaNodePointer tree) {
    if (tree != NULL) {
        if (tree->type == Internal)
            printPatricia(tree->Node.InternNode.left);
        if (tree->type == External)
            printf("%s\n", tree->Node.word);
        if (tree->type == Internal)
            printPatricia(tree->Node.InternNode.right);
    }
}

// Imprime dados estatísticos da árvore Patricia fornecida
void statsPatricia(PatriciaNodePointer tree) {
    printf("\t *** Dados da Arvore Patricia: *** \n");
    printf("Numero de nos internos Patricia: %d\n", nodeAmmountPatricia(tree, Internal));
    printf("Numero de nos externos Patricia: %d\n", nodeAmmountPatricia(tree, External));
    printf("Altura da Patricia: %d\n\n", heightPatricia(tree));
    printf("\t ********* \n");
}
