#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAXIMO 100005

// Função que retorna o máximo entre dois inteiros
// Função que retorna o máximo entre dois inteiros
int obterMaiorValor(int primeiroValor, int segundoValor)
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

// Função para calcular a pontuação máxima usando programação dinâmica
long long calcularPontuacaoMaximaDinamica(int *frequencia, int tamanhoMaximo)
{
    long long tabelaDePontuacoes[TAMANHO_MAXIMO] = {0};

    tabelaDePontuacoes[1] = frequencia[1];

    for (int i = 2; i < tamanhoMaximo; i++)
    {
        long long excluirPontuacao = tabelaDePontuacoes[i - 1];
        long long incluirPontuacao = tabelaDePontuacoes[i - 2] + (long long)frequencia[i] * i;
        tabelaDePontuacoes[i] = obterMaiorValor(excluirPontuacao, incluirPontuacao);
    }

    return tabelaDePontuacoes[tamanhoMaximo - 1];
}

// Função para calcular a pontuação máxima usando abordagem gulosa
long long calcularPontuacaoMaximaGulosa(int quantidadeDeElementos, int *sequencia)
{
    if (quantidadeDeElementos == 0)
    {
        return 0;
    }

    long long pontosAtuais = 0;
    long long pontosAnteriores = 0;

    for (int i = 0; i < quantidadeDeElementos; i++)
    {
        long long pontosTemp = pontosAtuais;
        pontosAtuais = obterMaiorValor(pontosAtuais, pontosAnteriores + (long long)sequencia[i] * i);
        pontosAnteriores = pontosTemp;
    }

    return pontosAtuais;
}

// Função para ler um inteiro da entrada
int lerInteiro(FILE *file)
{
    int valor;
    fscanf(file, "%d", &valor);
    return valor;
}

// Função para ler a sequência de inteiros de um arquivo
int *lerArquivo(const char *caminhoArquivo, int *quantidadeDeElementos)
{
    FILE *file = fopen(caminhoArquivo, "r");
    if (file == NULL)
    {
        printf("\n\033[0;31mErro ao abrir o arquivo: %s\033[0m\n\n", caminhoArquivo);
        exit(1);
    }

    *quantidadeDeElementos = lerInteiro(file);
    int *sequencia = (int *)malloc((*quantidadeDeElementos) * sizeof(int));

    for (int i = 0; i < *quantidadeDeElementos; i++)
    {
        fscanf(file, "%d", &sequencia[i]);
    }

    fclose(file);
    return sequencia;
}

// Função para inicializar um array de inteiros com zeros
void inicializarArrayComZeros(int tamanho, int *array)
{
    for (int i = 0; i < tamanho; i++)
    {
        array[i] = 0;
    }
}

// Função para calcular a frequência dos números na sequência
void calcularFrequencia(int quantidadeDeElementos, int *sequencia, int *frequencia)
{
    for (int i = 0; i < quantidadeDeElementos; i++)
    {
        int numero = sequencia[i];
        frequencia[numero]++;
    }
}

// Função para escrever um inteiro em um arquivo de saída
int escreverArquivo(const char *caminhoArquivoSaida, long long resultado)
{
    FILE *fileOut = fopen(caminhoArquivoSaida, "a");
    if (fileOut == NULL)
    {
        printf("\n\033[0;31mErro ao abrir o arquivo de saída: %s\033[0m\n\n", caminhoArquivoSaida);
        exit(1);
    }

    fprintf(fileOut, "%lld\n", resultado);
    fclose(fileOut);

    printf("\n\033[0;32mArquivo de saida gerado com sucesso!\033[0m\n\n");

    return 1;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("\n\033[0;31mERRO: Uso incorreto dos argumentos.\033[0m\n");
        printf("\033[0;31mUso correto: %s <estrategia> <arquivo_entrada.txt>\033[0m\n\n", argv[0]);
        return 1;
    }

    const char *caminhoArquivoEntrada = argv[2];
    const char *caminhoArquivoSaida = "saida.txt";

    int quantidadeDeElementos;
    int *sequencia = lerArquivo(caminhoArquivoEntrada, &quantidadeDeElementos);

    int frequencia[TAMANHO_MAXIMO];
    inicializarArrayComZeros(TAMANHO_MAXIMO, frequencia);
    calcularFrequencia(quantidadeDeElementos, sequencia, frequencia);

    long long pontuacaoMaxima;

    if (argv[1][0] == 'A')
    {
        pontuacaoMaxima = calcularPontuacaoMaximaGulosa(quantidadeDeElementos, sequencia);
    }
    else if (argv[1][0] == 'D')
    {
        pontuacaoMaxima = calcularPontuacaoMaximaDinamica(frequencia, TAMANHO_MAXIMO);
    }
    else
    {
        printf("\n\033[0;31mERRO: Estratégia desconhecida.\033[0m\n");
        printf("\033[0;31mUsar: <D> para programaçao dinamica ou <A> para estrategia alternetiva\033[0m\n\n");
        return 1;
    }

    escreverArquivo(caminhoArquivoSaida, pontuacaoMaxima);

    free(sequencia);

    return 0;
}