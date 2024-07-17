#include <stdio.h>
#include <stdlib.h>
#include "../Headers/Alternativa.h"


long long maiorValor(long long primeiroValor, long long segundoValor)
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

// Função recursiva com memoização para calcular a pontuação máxima usando DFS
long long calcularPontuacaoMaximaDFS(long long *sequencia, int tamanho, int indice, long long *memo)
{
    if (indice >= tamanho)
        return 0;

    if (memo[indice] != -1)
        return memo[indice];

    // Não escolher o elemento atual
    long long semEscolha = calcularPontuacaoMaximaDFS(sequencia, tamanho, indice + 1, memo);

    // Escolher o elemento atual
    long long comEscolha = sequencia[indice];
    if (indice + 2 < tamanho)
    {
        comEscolha += calcularPontuacaoMaximaDFS(sequencia, tamanho, indice + 2, memo);
    }

    // Escolher o máximo entre as duas opções
    memo[indice] = maiorValor(semEscolha, comEscolha);


    return memo[indice];
}


// Função para inicializar um array de long long com -1
long long *inicializarMemo(int tamanho)
{
    long long *memo = (long long *)malloc(tamanho * sizeof(long long));
    if (memo == NULL)
    {
        printf("\n\033[0;31mErro ao alocar memória para memo\033[0m\n\n");
        exit(1);
    }
    for (int i = 0; i < tamanho; i++)
    {
        memo[i] = -1;
    }
    return memo;
}

