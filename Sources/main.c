#include <stdio.h>
#include <stdlib.h>
#include "../Headers/Alternativa.h"
#include "../Headers/Arquivos.h"
#include "../Headers/ProgDinamica.h"
#include "../Headers/GerenciarTempo.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("\n\033[0;31mERRO: Uso incorreto dos argumentos.\033[0m\n");
        printf("\033[0;31mUso correto: %s <estrategia> <entrada.txt>\033[0m\n\n", argv[0]);
        return 1;
    }

    // Armazena o tempo de execução do programa.
    struct timeval tempoInicio, tempoFim, tempoDiferenca;

    // Variáveis para armazenar o tempo de início, fim e diferença.
    double tempoUsuarioInicio, tempoUsuarioFim, tempoSistemaInicio, tempoSistemaFim;

    // Variáveis para armazenar o tempo de início, fim e diferença completos.
    double tempoUsuarioCompleto, tempoSistemaCompleto, tempoGetTimeofDay, tempoRuUsage;

    const char *caminhoArquivoEntrada = argv[2];

    const char *caminhoArquivoSaida = "saida.txt";

    int quantidadeElementos;

    long long *sequencia = lerArquivo(caminhoArquivoEntrada, &quantidadeElementos);

    long long pontuacaoMaxima;

    if (argv[1][0] == 'D')
    {
        // Obtendo o tempo de início do sistema juntamente com o do usuario
        getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
        gettimeofday(&tempoInicio, NULL);

        pontuacaoMaxima = calcularPontuacaoMaximaDinamica(sequencia, quantidadeElementos);

        // Obtém o tempo do fim da execução.
        getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
        gettimeofday(&tempoFim, NULL);


    }
    else if (argv[1][0] == 'A')
    {
        // Obtendo o tempo de início do sistema juntamente com o do usuario
        getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
        gettimeofday(&tempoInicio, NULL);

        long long *memo = inicializarMemo(TAMANHO_MAXIMO);

        pontuacaoMaxima = calcularPontuacaoMaximaDFS(sequencia, quantidadeElementos, 0, memo);

        free(memo);

        // Obtém o tempo do fim da execução.
        getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
        gettimeofday(&tempoFim, NULL);
    }
    else
    {
        printf("\n\033[0;31mERRO: Estratégia desconhecida.\033[0m\n");
        printf("\033[0;31mUsar: <D> para programação dinâmica ou <A> para estratégia alternativa\033[0m\n\n");
        return 1;
    }

    escreverArquivo(caminhoArquivoSaida, pontuacaoMaxima);

    // Calculando a diferença de tempo
    timeval_subtract(&tempoDiferenca, &tempoFim, &tempoInicio);

    // Armazena os tempos em microssegundos
    tempoGetTimeofDay = joinTimes(tempoDiferenca.tv_sec, tempoDiferenca.tv_usec);
    tempoUsuarioCompleto = tempoUsuarioFim - tempoUsuarioInicio;
    tempoSistemaCompleto = tempoSistemaFim - tempoSistemaInicio;
    tempoRuUsage = tempoUsuarioCompleto + tempoSistemaCompleto;

    // Exibindo os resultados no terminal
    printTimes(tempoUsuarioCompleto, tempoSistemaCompleto, tempoRuUsage, tempoGetTimeofDay);

    free(sequencia);

    return 0;
}