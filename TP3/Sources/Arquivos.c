#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/Arquivos.h"
#include "../Headers/Input.h"

int escreverArquivo(const char *caminhoArquivoSaida, int *resultados, int numeroQueries, char algoritmo)
{
    FILE *fileOut = fopen(caminhoArquivoSaida, "w");
    if (fileOut == NULL)
    {
        printf("\n\033[0;31mErro ao abrir o arquivo de saída: %s\033[0m\n\n", caminhoArquivoSaida);
        exit(1);
    }
/////////////////////////////////////////////////
    if(algoritmo == 'S'){

        fprintf(fileOut,"Shift-And\n\n");
    }else{

        fprintf(fileOut,"BMHS\n\n");
    }
////////////////////////////////////////////////
    for(int i = 0; i < numeroQueries; i++){

        if(resultados[i] == 1){

            fprintf(fileOut, "sim\n");
        }else{

            fprintf(fileOut,"nao\n");
        }
        
    }
    
    fclose(fileOut);

    printf("\n\033[0;32mArquivo de saída gerado com sucesso!\033[0m\n\n");

    return 1;
}

int contarCaracteres(FILE *arquivo)
{
    int contador = 0;
    int caracter;

    long posicaoInicial = ftell(arquivo);

    // Conta os caracteres até o final da linha ou arquivo
    while ((caracter = fgetc(arquivo)) != EOF && caracter != '\n')
    {
        contador++;
    }

    fseek(arquivo, posicaoInicial, SEEK_SET);

    return contador;
}

Input lerArquivo(const char *CAMINHO_ARQUIVO)
{
    FILE *file;
    Input querie;
    int tamanho;
    int numeroColunas = 2;
    int linha = 0;

    file = fopen(CAMINHO_ARQUIVO, "r");

    if (file == NULL)
    {
        printf("\n\033[0;31mErro ao abrir o arquivo: %s\033[0m\n\n", CAMINHO_ARQUIVO);
        exit(1);
    }

    tamanho = contarCaracteres(file);

    querie.string = (char *)malloc((tamanho + 1) * sizeof(char));

    if (querie.string == NULL)
    {
        printf("\n\033[0;31mErro ao alocar memória para a string.\033[0m\n\n");
        exit(1);
    }

    if (fscanf(file, " %s", querie.string) != 1)
    {
        printf("\n\033[0;31mErro ao ler a string.\033[0m\n\n");
        exit(0);
    }

    tamanho = contarCaracteres(file);

    querie.subString = (char *)malloc((tamanho + 1) * sizeof(char));

    if (querie.subString == NULL)
    {
        printf("\n\033[0;31mErro ao alocar memória para a substring.\033[0m\n\n");
        exit(1);
    }

    if (fscanf(file, " %s", querie.subString) != 1)
    {
        printf("\n\033[0;31mErro ao ler a substring.\033[0m\n\n");
        exit(0);
    }

    if (fscanf(file, " %d", &querie.numeroQueries) != 1)
    {
        printf("\n\033[0;31mErro ao ler o numero de queries.\033[0m\n\n");
        exit(0);
    }

    querie.matrizQueries = (int **)malloc(querie.numeroQueries * sizeof(int *));

    if (querie.matrizQueries == NULL)
    {
        printf("\n\033[0;31mErro ao alocar memória para a matriz de queries.\033[0m\n\n");
        exit(1);
    }

    for (int i = 0; i < querie.numeroQueries; i++)
    {
        querie.matrizQueries[i] = (int *)malloc(numeroColunas * sizeof(int));

        if (querie.matrizQueries[i] == NULL)
        {
            printf("\n\033[0;31mErro ao alocar memória para uma linha da matriz de queries.\033[0m\n\n");
            exit(1);
        }
    }

    while (fscanf(file, " %d %d", &querie.matrizQueries[linha][0], &querie.matrizQueries[linha][1]) == 2)
    {
        linha++;
    }

    fclose(file);

    return querie;
}