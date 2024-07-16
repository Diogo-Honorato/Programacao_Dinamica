#include<stdio.h>
#include<stdlib.h>

int *lerArquivo(const char* CAMINHO_ARQUIVO){


    FILE *file;
    int indice = 0;
    int totalElementos;

    int *conteudoArquivo = NULL;


    file = fopen(CAMINHO_ARQUIVO, "r");

    if (file == NULL)
    {
        printf("\nErro ao abrir o arquivo: %s\n\n", CAMINHO_ARQUIVO);
        exit(0);
    }

    if (fscanf(file, " %d", &totalElementos) != 1)
    {
        printf("Erro ao ler o valor de total de elementos.\n");
        exit(0);
    }

    conteudoArquivo = (int*) malloc(totalElementos * sizeof(int));

    while(fscanf(file, " %d", &conteudoArquivo[indice]) == 1)
    {

        indice++;
    }

    fclose(file);


    return conteudoArquivo;
}

int escreverArquivo(const char* CAMINHO_ARQUIVO_SAIDA, int resultado){

    FILE *fileOut;

    fileOut = fopen(CAMINHO_ARQUIVO_SAIDA, "w");

    if (fileOut == NULL) { 
        
        printf("Erro ao abrir o arquivo output.");
        return 0;
    }

    fprintf(fileOut,"%d ",resultado);


    fclose(fileOut);

    return 1;

}





int main(int argc, char *argv[]){

    if (argc != 3) {
        printf("\nERRO: %s <estrategia> entrada.txt, multiplos comandos no terminal.\n", argv[0]);
        return 1;
    }

    


    int *array;

    char* arquivoEntrada = argv[2];

    char *arquivoSaida = "saida.txt";

    int num = 15;

    array = lerArquivo(arquivoEntrada);



    for(int i = 0; i < 12; i++){

        printf("%d ", array[i]);
    }


    escreverArquivo(arquivoSaida,num);
}