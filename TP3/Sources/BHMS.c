#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/BMHS.h"
#include "../Headers/Input.h"



int BMHS(char *texto, char *padrao, int inicio, int fim)
{
    int tamanhoTexto = fim - inicio + 1;
    int posicao;
    int tamanhoPadrao = strlen(padrao);
    int deslocamentoBmhs[MAX_CARACTERES];

    // se padrao > texto não haverá casamentos
    if (tamanhoPadrao > tamanhoTexto)
    {
        return 0;
    }

    // Preprocessamento para o algoritmo BMHS
    for (int i = 0; i < MAX_CARACTERES; i++)
    {
        deslocamentoBmhs[i] = tamanhoPadrao + 1;
    }

    for (int i = 0; i < tamanhoPadrao; i++)
    {
        deslocamentoBmhs[(unsigned char)padrao[i]] = tamanhoPadrao - i;
    }

    posicao = inicio + tamanhoPadrao - 1;

    while (posicao < inicio + tamanhoTexto)
    {
        int i = tamanhoPadrao - 1;
        while (i >= 0 && padrao[i] == texto[posicao - tamanhoPadrao + 1 + i])
        {
            i--;
        }

        if (i < 0)
        {
            return 1;
        }

        posicao = deslocamentoBmhs[(unsigned char)texto[posicao + 1]] + posicao;
    }

    return 0;
}