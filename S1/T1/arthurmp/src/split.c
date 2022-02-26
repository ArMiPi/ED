#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"split.h"

typedef struct _splited
{
    int num_substrings; // Número de substrings geradas
    char **substrings;  // Matriz contendo as substrings geradas
} _Splited;

/*
    # Saída:
        - _Splited: Struct
    
    # Descrição:
        - Aloca a memória necessária para uma instância inicial de _Splited

        - num_substrings = 0 e substrings = NULL

        - É necessário desalocar a memória utilizada pelo retorno dessa função
*/
_Splited *new_Splited() {
    _Splited *splt = (_Splited *) malloc(sizeof(_Splited));
    if(splt == NULL) {
        printf("ERROR: Could not allocate memory for Split\n");
        exit(EXIT_FAILURE);
    }

    // Valores iniciais
    splt->num_substrings = 0;
    splt->substrings = NULL;

    return splt;
}

/*
    # Entradas:
        - string, separator: String
    
    # Saída:
        - int
    
    # Descrição:
        - Retorna a quantidade de substrings que serão geradas a
          partir de string com base em separator
*/
int number_of_substrings(char *string, char *separator) {
    int quantity = 1;                           // Número mínimo de substrings
    int size_string = strlen(string);
    int size_separator= strlen(separator);

    // Localizar quantas vezes separator está presente em string
    for(int i = 0, j = 0; i <= size_string; i++) {
        if(string[i] != separator[j] && j > 0) j = 0;
        
        if(string[i] == separator[j]) j++;
        if(j == size_separator) {
            quantity++;
            j = 0;
        }
    }

    return quantity;
}

/*
    # Entrada:
        - size: Quantidade de posições do vetor
        
    # Saída:
        - int *: Vetor
    
    # Descrição:
        - Retorna um vetor de size posições

        - É necessário desalocar a memória utilizada pelo retorno dessa função
*/
int *newArray(int size) {
    int *pos_vector = (int *) malloc(size * sizeof(int));
    if(pos_vector == NULL) {
        printf("ERROR: Could not allocate memory for separator positions vector\n");
        exit(EXIT_FAILURE);
    }

    return pos_vector;
}

/*
    # Entradas:
        - num_substrings:       Quantidade de substrings que serão geradas
        - string, separator:    Strings
    
    # Saídas:
        - int *: Vetor
        - NULL
    
    # Descrição:
        - Retorna um vetor contendo a posição inicial das ocorrências de
          separator em string
        
        - Retorna NULL caso não seja possível criar o vetor

        - É necessário desalocar a memória utilizada pelo retorno dessa função
*/
int *separator_positions(int num_substrings, char *string, char *separator) {
    int *pos_vector = newArray(num_substrings);
    int size_separator = strlen(separator);

    // Localizar as posições que separator aparece em string
    for(int i = 0, j = 0, k = 0, temp; k < num_substrings - 1; i++) {
        if(string[i] != separator[j] && j > 0) j = 0;
        
        if(string[i] == separator[j]) {
            if(j == 0) temp = i;
            j++;
        }

        if(j == size_separator) {
            pos_vector[k] = temp;
            k++;
            j = 0;
        }
    }

    return pos_vector;
}

/*
    # Entradas:
        - num_substrings: Número de substrings
        - pos_separators: Posições onde ocorrerá a separação da string
        - string_size: Tamanho da string
        - separator_size: Tamanho do separator

    # Saída:
        - int *: Vetor
    
    # Descrição:
        - Retorna um vetor contendo o tamanho das substrings que serão geradas a partir de string

        - É necessário desalocar a memória utilizada pelo retorno dessa função
*/
int *substring_sizes(int num_substrings, int *pos_separators, int string_size, int separator_size) {
    int *size_vector = newArray(num_substrings);

    // Definir o tamanaho de cada substring gerada
    for(int i = 0, size; i < num_substrings; i++) {
        if(i == num_substrings - 1) size = string_size - (pos_separators[i-2] + separator_size);
        else if(i == 0) size = pos_separators[i];
        else size = pos_separators[i] - (pos_separators[i-1] + separator_size);

        size_vector[i] = size;
    }

    return size_vector;
}

/*
    # Entradas:
        - num_strings: Número de strings
        - size_strings: Vetor contendo os tamanahos das strings (sem considerar \0)
    
    # Saída:
        - char **: Matriz
    
    # Descrição:
        - Aloca a memória que será utilizada para armazenar as substrings de string

        - É necessário desalocar a memória utilizada pelo retorno dessa função
*/
char **newStringArray(int num_strings, int *size_strings) {
    char **splitMatrix = (char **) malloc(num_strings * sizeof(char *));
    if(splitMatrix == NULL) {
        printf("ERROR: Could not allocate memory for split matrix\n");
        exit(EXIT_FAILURE);
    }

    for(int i = 0; i < num_strings; i++) {
        splitMatrix[i] = (char *) malloc((size_strings[i] + 1) * sizeof(char));
        if(splitMatrix[i] == NULL) {
            printf("ERROR: Could not allocate memory for substring\n");
            exit(EXIT_FAILURE);
        }
    }

    return splitMatrix;
}

/*
    # Entradas:
        - num_substrings: Número de substrings
        - string: String que será separada
        - pos_separators: Posições onde ocorrerá a separação da string
        - size_substrings: Tamanho das substrings
        - string_size: Tamanho da string
    
    # Saídas:
        - char **: Matriz
        - NULL
    
    # Descrição: 
        - Gera uma matriz contendo as substrings geradas a partir de string tendo
          separator como base
        
        - Retorna NULL caso não seja possível criar a matriz
*/
char **substrings_matrix(char *string, char *separator, int num_substrings) {
    int string_size = strlen(string);
    int separator_size = strlen(separator);
    
    // Criar matriz vazia para as substrings
    int *pos_separators = separator_positions(num_substrings, string, separator);
    int *size_substrings = substring_sizes(num_substrings, pos_separators, string_size, separator_size);
    char **substrings = newStringArray(num_substrings, size_substrings);

    // Preencher a matriz
    // Primeira Substring
    int j;
    for(j = 0; j < size_substrings[0]; j++) substrings[0][j] = string[j];
    substrings[0][j] = '\0';

    int i, k;
    for(i = 1; i < num_substrings - 1; i++) {
        for(j = 0, k = pos_separators[i-1] + separator_size; j < size_substrings[i]; j++, k++) substrings[i][j] = string[k];
        substrings[i][j] = '\0';
    }

    // Última Substring
    for(j = 0, k = pos_separators[i-1] + separator_size; j < size_substrings[i]; j++, k++) substrings[i][j] = string[k];
    substrings[i][j] = '\0';

    // Liberar memória
    free(pos_separators);
    free(size_substrings);

    return substrings;
}

Splited split(char *string, char *separator) {
    // Verificar entradas
    if(string == NULL || separator== NULL) return NULL;
    if(strlen(string) == 0 || strlen(separator) == 0) return NULL;

    // Criar "objeto" Splited
    _Splited *splt = new_Splited();

    splt->num_substrings = number_of_substrings(string, separator);
    splt->substrings = substrings_matrix(string, separator, splt->num_substrings);

    return splt;
}

void printAllSubstrings(Splited splt) {
    _Splited *sptd = (_Splited *) splt;

    for(int i = 0; i < sptd->num_substrings; i++) {
        printf("[%d]: \"%s\"\n", i, sptd->substrings[i]);
    }
}

int getNumSubstrings(Splited splt) {
    _Splited *spltd = (_Splited *) splt;

    return spltd->num_substrings;
}

char *getSubstring(Splited splt, int position) {
    _Splited *spltd = (_Splited *) splt;

    return spltd->substrings[position];
}

char **getAllSubstrings(Splited splt) {
    _Splited *spltd = (_Splited *) splt;

    return spltd->substrings;
}

void destroySplited(Splited splt) {
    if(splt == NULL) return;

    _Splited *spltd = (_Splited *) splt;
    
    for(int i = 0; i < spltd->num_substrings; i++) free(spltd->substrings[i]);
    free(spltd->substrings);

    free(spltd);
    spltd = NULL;
}