#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/ShiftAnd.h"
#include "../Headers/Input.h"

int shiftAnd(char *texto, char *padrao, int inicio, int fim)
{
    int tamanhoTexto = fim - inicio + 1;
    int tamanhoPadrao = strlen(padrao);
    int estado = 0;
    int bitMasks[MAX_CARACTERES] = {0};

    // se padrao > texto não haverá casamentos
    if (tamanhoPadrao > tamanhoTexto)
    {
        return 0;
    }

    // Preprocessamento para o algoritmo Shift-And
    for (int posicao = 0; posicao < tamanhoPadrao; posicao++)
    {
        char caractereAtual = padrao[posicao];

        bitMasks[(unsigned char)caractereAtual] |= 1 << posicao;
    }

    for (int i = inicio; i <= fim; i++)
    {
        estado = ((estado << 1) | 1) & bitMasks[(unsigned char)texto[i]];

        if (estado & (1 << (tamanhoPadrao - 1)))
        {
            return 1;
        }
    }

    return 0;
}