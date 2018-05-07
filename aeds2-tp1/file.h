//
//  file.h
//  aeds2-tp1
//
//  Created by Gustavo Viegas on 05/05/18.
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

int alimentaDicionario(char *nomeArquivo, TSTNodePointer *TSTtree, PatriciaNodePointer *Pattree);
int leArquivo(char *nomeArquivo, TSTNodePointer TSTtree, PatriciaNodePointer Pattree);

#endif /* file_h */