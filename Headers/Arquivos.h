#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_
#include <stdio.h>

int lerInteiro(FILE *file);

long long *lerArquivo(const char *caminhoArquivo, int *quantidadeElementos);

int escreverArquivo(const char *caminhoArquivoSaida, long long resultado);


#endif