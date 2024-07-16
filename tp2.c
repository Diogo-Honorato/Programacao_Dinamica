#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAXIMO 100001

// Função para calcular o máximo entre dois inteiros
int obterMaiorValor(int primeiroValor, int segundoValor) {
    if (primeiroValor > segundoValor) {
        return primeiroValor;
    } else {
        return segundoValor;
    }
}

// Função recursiva com memoização para calcular a pontuação máxima usando DFS
int calcularPontuacaoMaximaDFS(int sequencia[], int tamanho, int indice, int *memo) {
    if (indice >= tamanho) return 0;
    if (memo[indice] != -1) return memo[indice];

    // Não escolher o elemento atual
    int semEscolha = calcularPontuacaoMaximaDFS(sequencia, tamanho, indice + 1, memo);

    // Escolher o elemento atual
    int comEscolha = sequencia[indice];
    if (indice + 2 < tamanho) {
        comEscolha += calcularPontuacaoMaximaDFS(sequencia, tamanho, indice + 2, memo);
    }

    // Escolher o máximo entre as duas opções
    memo[indice] = obterMaiorValor(semEscolha, comEscolha);
    return memo[indice];
}

// Função para calcular a pontuação máxima usando programação dinâmica
int calcularPontuacaoMaximaDinamica(int sequencia[], int tamanho) {
    if (tamanho == 0) return 0;
    if (tamanho == 1) return sequencia[0];

    int pontuacaoMaxima[TAMANHO_MAXIMO];
    pontuacaoMaxima[0] = sequencia[0];
    pontuacaoMaxima[1] = obterMaiorValor(sequencia[0], sequencia[1]);

    for (int i = 2; i < tamanho; ++i) {
        int escolha1 = pontuacaoMaxima[i - 1]; // Não escolher o elemento sequencia[i]
        int escolha2 = sequencia[i] + pontuacaoMaxima[i - 2]; // Escolher o elemento sequencia[i]

        pontuacaoMaxima[i] = obterMaiorValor(escolha1, escolha2);
    }

    return pontuacaoMaxima[tamanho - 1];
}

// Função para inicializar um array de inteiros com zeros
void inicializarArrayComZeros(int tamanho, int *array) {
    for (int i = 0; i < tamanho; i++) {
        array[i] = 0;
    }
}

// Função para ler um inteiro da entrada
int lerInteiro(FILE *file) {
    int valor;
    fscanf(file, " %d", &valor);
    return valor;
}

// Função para ler a sequência de inteiros de um arquivo
int *lerArquivo(const char *caminhoArquivo, int *quantidadeDeElementos) {
    FILE *file = fopen(caminhoArquivo, "r");
    if (file == NULL) {
        printf("\n\033[0;31mErro ao abrir o arquivo: %s\033[0m\n\n", caminhoArquivo);
        exit(1);
    }

    *quantidadeDeElementos = lerInteiro(file);
    int *sequencia = (int *)malloc((*quantidadeDeElementos) * sizeof(int));

    for (int i = 0; i < *quantidadeDeElementos; i++) {
        fscanf(file, " %d", &sequencia[i]);
    }

    fclose(file);
    return sequencia;
}

// Função para escrever um inteiro em um arquivo de saída
int escreverArquivo(const char *caminhoArquivoSaida, int resultado) {
    FILE *fileOut = fopen(caminhoArquivoSaida, "w");
    if (fileOut == NULL) {
        printf("\n\033[0;31mErro ao abrir o arquivo de saída: %s\033[0m\n\n", caminhoArquivoSaida);
        exit(1);
    }

    fprintf(fileOut, "%d\n", resultado);
    fclose(fileOut);

    printf("\n\033[0;32mArquivo de saída gerado com sucesso!\033[0m\n\n");

    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("\n\033[0;31mERRO: Uso incorreto dos argumentos.\033[0m\n");
        printf("\033[0;31mUso correto: %s <estrategia> <arquivo_entrada.txt>\033[0m\n\n", argv[0]);
        return 1;
    }

    const char *caminhoArquivoEntrada = argv[2];
    const char *caminhoArquivoSaida = "saida.txt";

    int quantidadeDeElementos;
    int *sequencia = lerArquivo(caminhoArquivoEntrada, &quantidadeDeElementos);

    int pontuacaoMaxima;

    if (argv[1][0] == 'D') {
        pontuacaoMaxima = calcularPontuacaoMaximaDinamica(sequencia, quantidadeDeElementos);
    } else if (argv[1][0] == 'A') {
        int *memo = (int *)malloc(TAMANHO_MAXIMO * sizeof(int));
        for (int i = 0; i < TAMANHO_MAXIMO; i++) {
            memo[i] = -1;
        }
        pontuacaoMaxima = calcularPontuacaoMaximaDFS(sequencia, quantidadeDeElementos, 0, memo);
        free(memo);
    } else {
        printf("\n\033[0;31mERRO: Estratégia desconhecida.\033[0m\n");
        printf("\033[0;31mUsar: <D> para programação dinâmica ou <A> para estratégia alternativa\033[0m\n\n");
        return 1;
    }

    escreverArquivo(caminhoArquivoSaida, pontuacaoMaxima);

    free(sequencia);

    return 0;
}
