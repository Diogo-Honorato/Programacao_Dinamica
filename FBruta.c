#include <stdio.h>
#include <stdlib.h>

#define MAX 100005

// Função que retorna o máximo entre dois inteiros
int maximo(int primeiroElemento, int segundoElemento)
{
    if (primeiroElemento > segundoElemento)
    {
        return primeiroElemento;
    }
    else
    {
        return segundoElemento;
    }
}

// Função para verificar se um elemento pode ser escolhido sem violar as regras do jogo
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

// Função para calcular a pontuação máxima utilizando força bruta
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
            maximoPontos = maximo(maximoPontos, somaAtual);
        }
    }

    return maximoPontos;
}

int main()
{
    int tamanho;
    scanf("%d", &tamanho);
    int sequencia[MAX];

    for (int i = 0; i < tamanho; i++)
    {
        scanf("%d", &sequencia[i]);
    }

    if (tamanho == 0)
    {
        printf("0\n");
        return 0;
    }

    // Chama a função de força bruta para calcular a pontuação máxima
    long long resultado = calcularPontuacaoMaximaForcaBruta(sequencia, tamanho);

    printf("%lld\n", resultado);

    return 0;
}