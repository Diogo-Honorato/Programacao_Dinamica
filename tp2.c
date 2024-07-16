#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAXIMO 100000

// Função que retorna o máximo entre dois inteiros
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

// Função para calcular a pontuação máxima usando programação dinâmica
long long calcularPontuacaoMaximaDinamica(int *frequencia, int tamanhoMaximo) {
    if (tamanhoMaximo == 0) {
        return 0;
    }

    long long tabelaDePontuacoes[TAMANHO_MAXIMO] = {0};

    tabelaDePontuacoes[0] = frequencia[0];
    if (tamanhoMaximo > 1) {
        tabelaDePontuacoes[1] = obterMaiorValor(frequencia[0], frequencia[1] * 1LL);
    }

    for (int i = 2; i < tamanhoMaximo; i++) {
        long long excluirPontuacao = tabelaDePontuacoes[i - 1];
        long long incluirPontuacao = tabelaDePontuacoes[i - 2] + (long long)frequencia[i] * i;
        tabelaDePontuacoes[i] = obterMaiorValor(excluirPontuacao, incluirPontuacao);
    }

    return tabelaDePontuacoes[tamanhoMaximo - 1];
}

// Função para calcular a frequência dos números na sequência
void calcularFrequencia(int quantidadeDeElementos, int *sequencia, int *frequencia) {
    for (int i = 0; i < quantidadeDeElementos; i++) {
        int numero = sequencia[i];
        frequencia[numero]++;
    }
}






//Busca exaustiva

int podeEscolher(int indice, int selecao, int tamanho)
{
    if (indice > 0 && (selecao & (1 << (indice - 1))))
    {
        return 0; // Verifica o elemento anterior
    }
    if (indice < tamanho - 1 && (selecao & (1 << (indice + 1))))
    {
        return 0; // Verifica o próximo elemento
    }
    return 1;
}


// Função para calcular a pontuação máxima usando busca exaustiva

long long calcularPontuacaoMaximaForcaBruta(int sequencia[], int tamanho)
{
    long long maximoPontos = 0;

    // Gera todos os subconjuntos possíveis da sequência
    for (int selecao = 0; selecao < (1 << tamanho); selecao++)
    {
        long long somaAtual = 0;
        int valido = 1;

        for (int i = 0; i < tamanho; i++)
        {
            if (selecao & (1 << i))
            {
                // Verifica se podemos escolher o elemento sequencia[i]
                if (!podeEscolher(i, selecao, tamanho))
                {
                    valido = 0;
                    break;
                }
                somaAtual += sequencia[i];
            }
        }

        // Se o subconjunto é válido, atualiza a pontuação máxima
        if (valido)
        {
            maximoPontos = obterMaiorValor(maximoPontos, somaAtual);
        }
    }

    return maximoPontos;
}

// Função para inicializar um array de inteiros com zeros
void inicializarArrayComZeros(int tamanho, int *array)
{
    for (int i = 0; i < tamanho; i++)
    {
        array[i] = 0;
    }
}


//Arquivos


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
        pontuacaoMaxima = calcularPontuacaoMaximaForcaBruta(sequencia, quantidadeDeElementos);
    }
    else if (argv[1][0] == 'D')
    {
        pontuacaoMaxima = calcularPontuacaoMaximaDinamica(frequencia, TAMANHO_MAXIMO);
    }
    else
    {
        printf("\n\033[0;31mERRO: Estratégia desconhecida.\033[0m\n");
        printf("\033[0;31mUsar: <D> para programação dinâmica ou <A> para estratégia alternativa\033[0m\n\n");
        return 1;
    }

    escreverArquivo(caminhoArquivoSaida, pontuacaoMaxima);

    printf("\n\n%lld\n\n",pontuacaoMaxima);

    free(sequencia);

    return 0;
}