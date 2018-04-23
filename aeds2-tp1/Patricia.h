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

#include<stdlib.h>
#include <sys/time.h>
#define D 8   /* depende de TipoChave */
#define MAX_SIZE 50
//
//typedef char* TipoChave; /* a definir, dependendo da aplicacao */
//typedef short TipoIndexAmp;
//typedef unsigned char TipoDib;
//typedef enum {
//    Interno, Externo
//} TipoNo;
//typedef struct TipoPatNo* TipoArvore;
//typedef struct TipoPatNo {
//    TipoNo nt;
//    union {
//        struct {
//            TipoIndexAmp Index;
//            char Compara;
//            TipoArvore Esq, Dir;
//        } NInterno;
//
//        TipoChave Chave;
//    } NO;
//} TipoPatNo;
//
////TipoDib Bit(TipoIndexAmp i, TipoChave k)
////{ /* Retorna o i-esimo bit da chave k a partir da esquerda */
////    int  c, j;
////    if (i == 0)
////        return 0;
////    else { c = k;
////        for (j = 1; j <= D - i; j++) c /= 2;
////        return (c & 1);
////    }
////}
//
//
//short EExterno(TipoArvore p)
//{ /* Verifica se p^ e nodo externo */
//    return (p->nt == Externo);
//}
//
//TipoArvore CriaNoInt(int i, TipoArvore *Esq,  TipoArvore *Dir, char Compara)
//{ TipoArvore p;
//    p = (TipoArvore)malloc(sizeof(TipoPatNo));
//    p->nt = Interno; p->NO.NInterno.Esq = *Esq;
//    p->NO.NInterno.Dir = *Dir; p->NO.NInterno.Index = i;
//    p->NO.NInterno.Compara = Compara;
//    return p;
//}
//
//TipoArvore CriaNoExt(TipoChave k)
//{ TipoArvore p;
//    p = (TipoArvore)malloc(sizeof(TipoPatNo));
//    p->nt = Externo; p->NO.Chave = k; return p;
//}
//
//void Pesquisa(TipoChave k, TipoArvore t)
//{ if (EExterno(t))
//{ if (k == t->NO.Chave)
//    printf("Elemento encontrado\n");
//else printf("Elemento nao encontrado\n");
//    return;
//}
//    if (k[t->NO.NInterno.Index] <= t->NO.NInterno.Compara) {
//        Pesquisa(k, t->NO.NInterno.Esq);
//    } else {
//        Pesquisa(k, t->NO.NInterno.Dir);
//    }
//}
//
//TipoArvore InsereEntre(TipoChave k, TipoArvore *t, int i)
//{ TipoArvore p;
//    if (EExterno(*t) || i < (*t)->NO.NInterno.Index)
//    { /* cria um novo no externo */
//        p = CriaNoExt(k);
//        if (Bit(i, k) == 1)
//            return (CriaNoInt(i, t, &p));
//        else return (CriaNoInt(i, &p, t));
//    }
//    else
//    { if (Bit((*t)->NO.NInterno.Index, k) == 1)
//        (*t)->NO.NInterno.Dir = InsereEntre(k,&(*t)->NO.NInterno.Dir,i);
//    else
//        (*t)->NO.NInterno.Esq = InsereEntre(k,&(*t)->NO.NInterno.Esq,i);
//        return (*t);
//    }
//}
//
//TipoArvore Insere(TipoChave k, TipoArvore *t) {
//    TipoArvore p;
//    int i;
//    if (*t == NULL)
//        return (CriaNoExt(k));
//    else {
//        p = *t;
//        int ultimoIndex;
//
//        while (!EExterno(p)) {
//            ultimoIndex = p->NO.NInterno.Index;
//
//            if (k[p->NO.NInterno.Index] <= p->NO.NInterno.Compara) {
//                p = p->NO.NInterno.Esq;
//            } else {
//                p = p->NO.NInterno.Dir;
//            }
//        }
//
//        for (i = ultimoIndex; i < MAX_SIZE; i++) {
//            if (k[i] != p->NO.NInterno.Compara) {
//                return InsereEntre(k, t, i);
//            }
//        }
//
//        printf("Erro; chave ja na arvore \n");
//        return 0;
//}
//
//int main(int argc, char *argv[])
//{ TipoArvore a = NULL;
//    TipoChave c;
//    int  i, j, k, n;
//    int  min = 32, max = 126;
//    TipoChave vetor[95];
//    /* Gera uma permutacao aleatoria de chaves dos caracteres ASCII 32 a  126 */
//    struct timeval semente;
//    gettimeofday(&semente,NULL);
//    srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
//    for (i = min; i <= max; i++)
//        vetor[i - 32] = i;
//    for (i = min; i <= max; i++)
//    { k = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
//        j = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
//        n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n;
//    }
//    /* Insere cada chave na arvore */
//    for (i = min; i <= max; i++)
//    { c = vetor[i - 32]; printf("Inserindo chave: %c\n", c);
//        a = Insere(c, &a);
//    }
//    /* Gera outra permutacao aleatoria de chaves */
//    for (i = min; i <= max; i++)
//    { k = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
//        j = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
//        n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n;
//    }
//    /* Pesquisa cada chave na arvore */
//    for (i = min; i <= max; i++)
//    { c = vetor[i - 32]; printf("Pesquisando chave: %c\n", c);
//        Pesquisa(c, a);
//    }
//    return 0;
//}


#endif /* Patricia_h */
