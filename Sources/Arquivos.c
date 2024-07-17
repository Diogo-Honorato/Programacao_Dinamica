#include <stdio.h>
#include <stdlib.h>
#include "../Headers/Arquivos.h"

// Função para ler um inteiro da entrada
int lerInteiro(FILE *file)
{
    int valor;
    if (fscanf(file, " %d", &valor) == 1)
    {

        return valor;
    }

    return 0;
}

// Função para ler a sequência de inteiros de um arquivo
long long *lerArquivo(const char *caminhoArquivo, int *quantidadeElementos)
{
    FILE *file = fopen(caminhoArquivo, "r");

    if (file == NULL)
    {
        printf("\n\033[0;31mErro ao abrir o arquivo: %s\033[0m\n\n", caminhoArquivo);
        exit(1);
    }

    *quantidadeElementos = lerInteiro(file);

    long long *sequencia = (long long *)malloc((*quantidadeElementos) * sizeof(long long));

    for (int i = 0; i < *quantidadeElementos; i++)
    {
        if (fscanf(file, " %lld", &sequencia[i]) != 1)
        {
            printf("\n\033[0;31mErro ao ler o elemento %d do arquivo\033[0m\n\n", i);
            exit(1);
        }
    }

    fclose(file);

    return sequencia;
}

// Função para escrever um inteiro em um arquivo de saída
int escreverArquivo(const char *caminhoArquivoSaida, long long resultado)
{
    FILE *fileOut = fopen(caminhoArquivoSaida, "w");
    if (fileOut == NULL)
    {
        printf("\n\033[0;31mErro ao abrir o arquivo de saída: %s\033[0m\n\n", caminhoArquivoSaida);
        exit(1);
    }

    fprintf(fileOut, "%lld\n", resultado);
    fclose(fileOut);

    printf("\n\033[0;32mArquivo de saída gerado com sucesso!\033[0m\n\n");

    return 1;
}