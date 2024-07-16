#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerarArquivoEntrada(const char *nomeArquivo, int N, int minVal, int maxVal) {
    FILE *arquivo = fopen(nomeArquivo, "w");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    fprintf(arquivo, "%d\n", N);

    srand(time(NULL));
    for (int i = 0; i < N; i++) {
        int valor = minVal + rand() % (maxVal - minVal + 1);
        fprintf(arquivo, "%d ", valor);
    }
    fprintf(arquivo, "\n");

    fclose(arquivo);
    printf("Arquivo '%s' gerado com sucesso!\n", nomeArquivo);
}

int main() {
    int N;
    int minVal = 0;
    int maxVal = 100;

    printf("Digite o número de elementos: ");
    scanf("%d", &N);

    gerarArquivoEntrada("entrada.txt", N, minVal, maxVal);
    return 0;
}