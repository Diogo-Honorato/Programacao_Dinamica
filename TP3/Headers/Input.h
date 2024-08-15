#ifndef _INPUT_H_
#define _INPUT_H_

#define MAX_CARACTERES 256

typedef struct Input
{
    char *string;
    char *subString;
    int numeroQueries;
    int **matrizQueries;
} Input;

#endif