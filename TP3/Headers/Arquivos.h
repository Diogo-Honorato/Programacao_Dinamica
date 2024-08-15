#ifndef _ARQUIVOS_H_
#define _ARQUIVOS_H_
#include <stdio.h>
#include "Input.h"

int escreverArquivo(const char *caminhoArquivoSaida, int *resultados, int numeroQueries, char algoritmo);

int contarCaracteres(FILE *arquivo);

Input lerArquivo(const char *CAMINHO_ARQUIVO);



#endif