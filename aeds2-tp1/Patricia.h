//
//  Patricia.h
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 19/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//
//  Implementação da árvore Patrícia feita pelo Professor Ziviani, com alterações do trio para aceitar strings.
//  A inserção teve ajuda do trio Lucas Duarte, Vitor Luis e Vinicius Gabriel! #thanks
//

#ifndef Patricia_h
#define Patricia_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#define D 8
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


/**
 Verifica se um certo nó da árvore é externo ou não
 
 @param node Ponteiro para o nó a ser analisado
 @return Inteiro representando se o nó é externo (1) ou não (0)
 */
short isExternal(PatriciaNodePointer node);

/**
 Percorre a árvore Patricia a fim de descobrir a sua altura

 @param tree Ponteiro pra árvore Patricia a ser percorrida
 @return Inteiro representando a altura da árvore processada
 */
int heightPatricia(PatriciaNodePointer tree);

/**
 Cria um novo nó interno na árvore, alocando a memória e apontando os dados passados

 @param left Ponteiro à esquerda do nó
 @param right Ponteiro à direita do nó
 @param index Índice a ser comparado quando percorrer esse nó
 @param compare Caracter a ser comparado quando percorrer esse nó
 @return Ponteiro para o nó recém-criado
 */
PatriciaNodePointer createInternalNodePatricia(PatriciaNodePointer *left, PatriciaNodePointer *right, int index, char compare);


/**
 Cria um novo nó externo na árvore, alocando a memória e setando os dados passados

 @param word Palavra a ser salva no nó
 @param p Ponteiro para o ponteiro do nó a ser criado
 @return Ponteiro para o nó recém-criado
 */
PatriciaNodePointer createExternalNodePatricia(String word, PatriciaNodePointer *p);


/**
 Pesquisa uma palavra na árvore, percorrendo recursivamente até encontrar (ou não) a palavra

 @param word Palavra a ser buscada na árvore
 @param tree Ponteiro para a árvore a ser percorrida
 @param comparisons Ponteiro para um inteiro que salva o número de comparações feitas
 @param height Ponteiro para um inteiro que salva a altura percorrida
 @return Inteiro representando se a palavra foi encontrada (1) ou não
 */
short searchPatricia(String word, PatriciaNodePointer tree, int *comparisons, int *height);


/**
 Insere um nó na árvore, criando nós internos, se necessário, para alocar uma nova palavra à árvore

 @param word Palavra a ser inserida na árvore
 @param tree Ponteiro para o ponteiro da árvore a ser inserida
 @param index Índice que difere a palavra da árvore
 @param differentChar Caracter que difere a palavra da árvore
 @return Ponteiro para o último nó chamado recursivamente da árvore após inserção
 */
PatriciaNodePointer insertBetweenPatricia(String word, PatriciaNodePointer *tree, int index, char differentChar);


/**
 Chama as funções necessárias e análise de onde difere para inserir uma nova palavra à árvore

 @param word Palavra a ser inserida na árvore
 @param tree Ponteiro para o ponteiro da árvore a ser manipulada
 @return Ponteiro para a árvore manipulada
 */
PatriciaNodePointer insertPatricia(String word, PatriciaNodePointer *tree);

/**
 Registra a quantidade de nós em uma sub-árvore Patrícia, recursivamente

 @param tree Ponteiro para a árvore a ser verificada
 @param internalNodes Ponteiro que registra quantidade de nós internos encontrados
 @param externalNodes Ponteiro que registra quantidade de nós externos encontrados
 */
void nodeCountPatricia(PatriciaNodePointer tree, int *internalNodes, int *externalNodes);


/**
 Retorna a quantidade de nós encontrados em uma árvore Patricia, de um determinado tipo

 @param tree Ponteiro para a árvore a ser verificada
 @param nodeType Tipo de nó a ser contabilizado
 @return Quantidade de nós do tipo nodeType que foi encontrado na árvore
 */
int nodeAmmountPatricia(PatriciaNodePointer tree, PatriciaNodeType nodeType);


/**
 Percorre uma árvore patricia, imprimindo os seus registros

 @param tree Ponteiro para a árvore a ser impressa
 */
void printPatricia(PatriciaNodePointer tree);

/**
 Imprime dados estatísticos da árvore Patricia fornecida

 @param tree Ponteiro para a árvore a ser analisada
 */
void statsPatricia(PatriciaNodePointer tree);

//void proccessTST(FILE *loadedFile, TSTNodePointer treeTST);

//void proccessPatricia(FILE *loadedFile, PatriciaNodePointer treePatricia);


#endif /* Patricia_h */
