#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Headers/GerenciarTempo.h"
#include "../Headers/Arquivos.h"
#include "../Headers/BMHS.h"
#include "../Headers/Input.h"
#include "../Headers/ShiftAnd.h"


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

    Input input = lerArquivo(caminhoArquivoEntrada);

    int resultados[input.numeroQueries];

    if (argv[1][0] == 'B')
    {
        // Obtendo o tempo de início do sistema juntamente com o do usuario
        getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
        gettimeofday(&tempoInicio, NULL);

        for (int i = 0; i < input.numeroQueries; i++)
        {
            // Ajusta os índices de início e fim para zero-based
            int inicio = input.matrizQueries[i][0] - 1;
            int fim = input.matrizQueries[i][1] - 1;

            // Busca utilizando BMHS
            if (BMHS(input.string, input.subString, inicio, fim))
            {
                resultados[i] = 1;
            }
            else
            {
                resultados[i] = 0;
            }
        }

        // Obtém o tempo do fim da execução.
        getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
        gettimeofday(&tempoFim, NULL);
    }
    else if (argv[1][0] == 'S')
    {
        // Obtendo o tempo de início do sistema juntamente com o do usuario
        getUsageNow(&tempoUsuarioInicio, &tempoSistemaInicio);
        gettimeofday(&tempoInicio, NULL);

        for (int i = 0; i < input.numeroQueries; i++)
        {   
            // Ajusta os índices de início e fim para zero-based
            int inicio = input.matrizQueries[i][0] - 1;
            int fim = input.matrizQueries[i][1] - 1;

            // Busca utilizando Shift-And
            if (shiftAnd(input.string, input.subString, inicio, fim))
            {
                resultados[i] = 1;
            }
            else
            {
                resultados[i] = 0;
            }

            // Obtém o tempo do fim da execução.
           getUsageNow(&tempoUsuarioFim, &tempoSistemaFim);
           gettimeofday(&tempoFim, NULL);
        }
    }
    else
    {
        printf("\n\033[0;31mERRO: Estratégia desconhecida.\033[0m\n");
        printf("\033[0;31mUsar: <B> para utilizar o BHMS ou <S> para utilizar o Shift-And\033[0m\n\n");
        return 1;
    }

    escreverArquivo(caminhoArquivoSaida,resultados,input.numeroQueries,argv[1][0]);

    // Calculando a diferença de tempo
    timeval_subtract(&tempoDiferenca, &tempoFim, &tempoInicio);

    // Armazena os tempos em microssegundos
    tempoGetTimeofDay = joinTimes(tempoDiferenca.tv_sec, tempoDiferenca.tv_usec);
    tempoUsuarioCompleto = tempoUsuarioFim - tempoUsuarioInicio;
    tempoSistemaCompleto = tempoSistemaFim - tempoSistemaInicio;
    tempoRuUsage = tempoUsuarioCompleto + tempoSistemaCompleto;

    // Exibindo os resultados no terminal
    printTimes(tempoUsuarioCompleto, tempoSistemaCompleto, tempoRuUsage, tempoGetTimeofDay);

    



    free(input.string);
    free(input.subString);
    for (int i = 0; i < input.numeroQueries; i++)
    {
        free(input.matrizQueries[i]);
    }
    free(input.matrizQueries);

    return 1;
}
