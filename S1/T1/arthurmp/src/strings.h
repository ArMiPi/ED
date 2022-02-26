#ifndef STRINGS_H
#define STRINGS_H

#include <stdbool.h>

/*
    - Esse módulo tem por objetivo implementar um tipo string,
      bem como funções para trabalhar com esse tipo

    - Todas as strings utilizadas nas chamadas das funções devem
      ser != NULL
*/

typedef char* string;

/*
    # Entrada:
        - size: Tamanho a ser armazenado (Não incluir \0)
    
    # Saída:
        - string: char *
    
    # Descrição:
        - Retorna um ponteiro com capacidade para size caracteres;

        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
string newEmptyString(int size);

/*
    # Entrada:
        - str: String
    
    # Saída:
        - string: char *
    
    # Descrição:
        - Cria uma string com conteúdo str;

        - É necessário desalocar a memória utilizada pelo
          retorno dessa função
*/
string copyString(string str);

/*
    # Entradas:
        - str1, str2: Strings

    # Saída:
        - string: char *

    # Descrição:
        - Retorna uma string onde str2 é concatenada ao final de str1
*/
string concat(string str1, string str2);

/*
    # Entradas:
        - str1: String
        - start: Posição inicial
        - end: Posição final
    
    # Saídas:
        - string: char*
        - NULL
    
    # Descrição:
        - Retorna uma string contendo o conteúdo de
          str das posições start à end
        
        - Ex: slice("example", 2, 5) -> "ampl"

        - start && end devem estar dentro dos limites {0, strlen(str)}

        - É necessário desalocar a memória utilizada pelo retorno dessa
          função
*/
string slice(string str, int start, int end);

/*
    # Entradas:
        - str1, str2: Strings
    
    # Saídas:
        - bool
    
    # Descrição:
        - Retorna true se str1 iniciar com str2, false caso contrário
*/
bool startsWith(string str1, string str2);

/*
    # Entradas:
        - str1, str2: Strings
    
    # Saídas:
        - bool
    
    # Descrição:
        - Retorna true se str1 terminar com str2, false caso contrário
*/
bool endsWith(string str1, string str2);

/*
    # Entradas:
        - str1, str2: Strings
    
    # Saídas:
        - -1
        - int >= 0 < strlen(str1)
    
    # Saídas:
        - Retorna -1 se str1 não possuir str2, ou retorna
          a primeira posição em str1 na qual str2 inicia
        
        - Ex: contains("example", "amp") -> 2
*/
int contains(string str1, string str2);

/*
    # Entradas:
        - num_strings: Quantidade de strings
        - strings: Vetor de strings
        - joiner: string
    
    # Saída:
        - string: char *
    
    # Descrição:
        - Retorna uma string unindo todas as strings
          de strings com joiner sendo colocado entre
          elas
*/
string join(int num_strings, string *strings, string joiner);

#endif