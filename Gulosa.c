#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

// Função para comparar inteiros (usada no qsort)
int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int main() {
    int n;
    scanf("%d", &n);
    
    if (n == 0) {
        printf("0\n");
        return 0;
    }
    
    int a[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    
    // Ordenar a sequência em ordem decrescente
    qsort(a, n, sizeof(int), compare);
    
    int maxPoints = 0;
    int i = 0;
    
    while (i < n) {
        int current = a[i];
        int count = 0;
        
        // Contar a frequência do elemento atual
        while (i < n && a[i] == current) {
            count++;
            i++;
        }
        
        // Adicionar os pontos do elemento atual
        maxPoints += current * count;
        
        // Pular os elementos adjacentes
        while (i < n && (a[i] == current - 1 || a[i] == current + 1)) {
            i++;
        }
    }
    
    printf("%d\n", maxPoints);
    return 0;
}
