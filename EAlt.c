#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

// Função para comparar inteiros (usada no qsort)
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

// Função que retorna o máximo entre dois inteiros
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Função recursiva para calcular a pontuação máxima
long long maxPoints(int freq[], int i) {
    if (i <= 0) {
        return 0;
    }
    if (freq[i] == 0) {
        return maxPoints(freq, i-1);
    }
    return max(maxPoints(freq, i-1), maxPoints(freq, i-2) + (long long)freq[i] * i);
}

int main() {
    int n;
    int freq[MAX] = {0}; // Frequência dos números na sequência

    // Leitura da entrada
    scanf("%d", &n);
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
        freq[a[i]]++;
    }

    // Calcular a pontuação máxima usando a função recursiva
    long long result = maxPoints(freq, MAX-1);

    printf("%lld\n", result);

    return 0;
}
