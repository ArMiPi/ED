#ifndef FORMS_H
#define FORMS_H

#include"llist.h"
#include"strings.h"

/*
    - Esse módulo tem por objetivo melhor organizar as formas que são obtidas pelo .geo

    - Formas:
        -> c: Círculo
        -> r: Retângulo
        -> l: Reta
        -> t: Texto
*/

typedef void *form;

/*
    # Entrada:
        - instruction: Comando do .geo para criar a forma
    
    # Saída:
        - form: Struct
    
    # Descrição:
        - Reorna uma nova forma

        - instruction != NULL
*/
form newForm(string instruction);

/*
    # Entrada:
        - instructions: Comandos do .geo para criar as formas
    
    # Saída:
        - llist: Lista com as formas
    
    # Descrição:
        - Retorna uma lista contendo todas as formas indicadas em
          instructions
*/
llist formsList(llist instructions);

/*
    # Entrada: 
        - format: Forma
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna o tipo da forma
          (círculo, retângulo, linha ou texto)
*/
string getFormType(form format);

/*
    # Entrada:
        - format: Forma
    
    # Saída:
        - void*: Pointeiro
    
    # Descrição:
        - Retorna um ponteiro para o endereço contendo
          as informações da forma em format
*/
void *getFormInfo(form format);

/*
    # Entrada:
        - format: Forma
    
    # Descrição:
        - Libera a memória utilizada por format
*/
void destroyForm(form format);

#endif