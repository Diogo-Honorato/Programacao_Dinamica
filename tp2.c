#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAXIMO 100005

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

// Função para calcular a pontuação máxima usando busca exaustiva
long long calcularPontuacaoMaximaExaustiva(int *sequencia, int tamanho)
{
    if (tamanho == 0)
    {
        return 0;
    }

    // Variável para armazenar a pontuação máxima encontrada
    long long maximoPontuacao = 0;

    // Percorrer todas as possíveis escolhas de elementos para remoção
    for (int i = 0; i < tamanho; i++)
    {
        // Calculando a pontuação para a jogada atual
        long long pontosJogadaAtual = (long long)sequencia[i] * i;

        // Calculando o tamanho da nova sequência
        int tamanhoNovaSequencia = tamanho - 3;
        if (tamanhoNovaSequencia <= 0)
        {
            continue; // Ignora esta iteração se não houver elementos suficientes para formar uma nova sequência
        }

        // Criando uma nova sequência sem o elemento atual e seus vizinhos
        int *novaSequencia = (int *)malloc(tamanhoNovaSequencia * sizeof(int));
        if (novaSequencia == NULL)
        {
            printf("\n\033[0;31mErro ao alocar memória para nova sequência.\033[0m\n\n");
            exit(1);
        }

        int indiceNovaSequencia = 0;

        for (int j = 0; j < tamanho; j++)
        {
            if (j == i || j == i + 1 || j == i - 1)
            {
                continue;
            }
            novaSequencia[indiceNovaSequencia++] = sequencia[j];
        }

        // Chamada recursiva para calcular a pontuação máxima para a nova sequência
        long long pontuacaoRestante = calcularPontuacaoMaximaExaustiva(novaSequencia, tamanhoNovaSequencia);

        // Atualizar a pontuação máxima encontrada até agora
        maximoPontuacao = obterMaiorValor(maximoPontuacao, pontosJogadaAtual + pontuacaoRestante);

        // Liberar memória alocada dinamicamente
        free(novaSequencia);
    }

    return maximoPontuacao;
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
        pontuacaoMaxima = calcularPontuacaoMaximaExaustiva(sequencia, quantidadeDeElementos);
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

    free(sequencia);

    return 0;
}