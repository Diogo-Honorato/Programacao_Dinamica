#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

// Função que retorna o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

int main() {
    int n;
    int freq[MAX] = {0}; // Frequência dos números na sequência
    long long dp[MAX] = {0}; // dp[i] vai guardar a pontuação máxima que podemos conseguir até o número i

    // Leitura da entrada
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        freq[a[i]]++;
    }

    // Base da DP
    dp[1] = freq[1];

    // Preenchendo a tabela DP
    for (int i = 2; i < MAX; i++) {
        dp[i] = max(dp[i-1], dp[i-2] + (long long)freq[i] * i);
    }

    // A resposta está em dp[MAX-1]
    printf("%lld\n", dp[MAX-1]);

    return 0;
}