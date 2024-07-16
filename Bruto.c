#include <stdio.h>
#include <stdlib.h>

#define MAXN 100001

// Função para calcular o máximo de dois números
int maximo(int a, int b) {
    return (a > b) ? a : b;
}

// Função recursiva com memoização para calcular a pontuação máxima
int calcularPontuacao(int sequencia[], int n, int indice, int *memo) {
    if (indice >= n) return 0;
    if (memo[indice] != -1) return memo[indice];

    // Caso não escolher o elemento atual
    int semEscolha = calcularPontuacao(sequencia, n, indice + 1, memo);

    // Caso escolher o elemento atual
    int comEscolha = sequencia[indice];
    if (indice + 1 < n) comEscolha += calcularPontuacao(sequencia, n, indice + 2, memo);

    // Escolher o máximo entre as duas opções
    memo[indice] = maximo(semEscolha, comEscolha);
    return memo[indice];
}

// Função principal
int main() {
    int n;
    scanf("%d", &n);

    int sequencia[MAXN];
    for (int i = 0; i < n; ++i) {
        scanf("%d", &sequencia[i]);
    }

    // Inicializar o array de memoização com -1 (significa que o valor ainda não foi calculado)
    int memo[MAXN];
    for (int i = 0; i < n; ++i) {
        memo[i] = -1;
    }

    // Calcular a pontuação máxima a partir do índice 0 da sequência
    int resultado = calcularPontuacao(sequencia, n, 0, memo);
    printf("%d\n", resultado);

    return 0;
}
