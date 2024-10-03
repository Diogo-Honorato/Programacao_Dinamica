#INTRODUÇÃO#

João não gosta de sentir tédio. É por isso que sempre que fica entediado, ele inventa jogos. Em
uma longa noite de inverno, ele inventou um jogo e decidiu jogá-lo.
Dada uma sequência a composta por n inteiros. O jogador pode fazer várias jogadas. Em cada
jogada ele pode escolher um elemento da sequência (vamos denotá-lo ak ) e excluí-lo, sendo que
os elementos ak+1 e ak−1 também devem ser excluídos da sequência. Essa jogadas traz ak pontos
para o jogador.
João é um perfeccionista, então decidiu conseguir o máximo de pontos possível. Para isso João
pediu para você criar um programa que mostre a qual a pontuação máxima que é possível atingir
em cada jogo.
Assim, seu objetivo nesse trabalho é implementar duas estratégias para solucionar esse problema:
• Uma estratégia por Programação Dinâmica;
• Uma estratégia alternativa que seja capaz de sempre resolver o problema;
Entrada e Saída
A primeira linha contém o inteiro N (0 ≤ N ≤ 105
) que mostra quantos números existem na
sequência de Joâo.
A segunda linha contém N inteiros a1, a2, ..., an.

Exemplo de entrada:

9

1 2 1 3 2 2 2 2 3

Exemplo de saída

10

O atende por tp2 e será chamado da seguinte forma:
./tp2 <estrategia> entrada.txt Onde:

• <estrategia> é D para a solução baseada em programação dinâmica e A para a solução
alternetiva;

O programa deve criar um arquivo saida.txt com a resposta, na tela, e também deve imprimir apenas os tempos de usuário e os tempos de sistema para comparação.
