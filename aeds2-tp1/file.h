//
//  file.h
//  aeds2-tp1
//
//  Created by  Bruno Marra (3029), Gustavo Viegas (3026) e Heitor Passeado (3055) on 10/04/18.
//  Copyright © 2018 UFV Florestal. All rights reserved.
//

#ifndef file_h
#define file_h

#include <ctype.h>
#include <stdio.h>
#include "TST.h"
#include "Patricia.h"
#include <string.h>
#include <stdlib.h>

#define BUFFERSIZE 255


/**
 Alimenta o dicionário, lendo o arquivo e inserindo seus valores nas árvores fornecidas

 @param fileName Caminho do arquivo do dicionário
 @param treeTST Ponteiro para árvore TST que será preenchida
 @param treePatricia Ponteiro para árvore Patricia que será preenchida
 @return Inteiro representando se o arquivo foi lido corretamente (1) ou não (0)
 */
int feedDictionary(char *fileName, TSTNodePointer *treeTST, PatriciaNodePointer *treePatricia);


/**
 Lê um arquivo e processa as árvores fornecidas, buscando as palavras no dicionário

 @param fileName Caminho do arquivo a ser processado
 @param treeTST Ponteiro para árvore TST que será processada
 @param treePatricia Ponteiro para árvore Patricia que será processada
 @return Inteiro representando se o arquivo foi lido corretamente (1) ou não (0)
 */
int readFile(char *fileName, TSTNodePointer treeTST, PatriciaNodePointer treePatricia);


/**
 Processa a árvore TST, comparando cada palavra lida na árvore TST fornecida

 @param loadedFile Arquivo carregado com as palavras a serem lidas
 @param treeTST Ponteiro para árvore TST que será processada
 */
void proccessTST(FILE *loadedFile, TSTNodePointer treeTST);

/**
 Processa a árvore Patricia, comparando cada palavra lida na árvore TST fornecida
 
 @param loadedFile Arquivo carregado com as palavras a serem lidas
 @param treePatricia Ponteiro para árvore Patricia que será processada
 */
void proccessPatricia(FILE *loadedFile, PatriciaNodePointer treePatricia);
#endif /* file_h */
