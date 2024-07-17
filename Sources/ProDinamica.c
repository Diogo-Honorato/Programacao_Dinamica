#include <stdio.h>
#include <stdlib.h>
#include "../Headers/ProgDinamica.h"

// Função para calcular o máximo entre dois inteiros long long
long long obterMaiorValor(long long primeiroValor, long long segundoValor)
{
    if (primeiroValor > segundoValor)
    {
        return primeiroValor;
    }
    else
    {
        return segundoValor;
    }
}

long long calcularPontuacaoMaximaDinamica(long long *sequencia, int tamanho)
{
    if (tamanho == 0)
        return 0;

    if (tamanho == 1)
        return sequencia[0];

    long long pontuacaoMaxima[TAMANHO_MAXIMO];

    pontuacaoMaxima[0] = sequencia[0];

    pontuacaoMaxima[1] = obterMaiorValor(sequencia[0], sequencia[1]);

    for (int i = 2; i < tamanho; ++i)
    {
        long long escolha1 = pontuacaoMaxima[i - 1];     // Não escolher o elemento sequencia[i]

        long long escolha2 = sequencia[i] + pontuacaoMaxima[i - 2]; // Escolher o elemento sequencia[i]

        pontuacaoMaxima[i] = obterMaiorValor(escolha1, escolha2);
    }



    return pontuacaoMaxima[tamanho - 1];
}

void inicializarArrayComZeros(int tamanho, long long *array)
{
    for (int i = 0; i < tamanho; i++)
    {
        array[i] = 0;
    }
}