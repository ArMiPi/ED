#ifndef FORMS_H
#define FORMS_H

#include"llist.h"
#include"strings.h"

/*
    - Esse módulo tem por objetivo facilitar a obtenção de informações das formas contidas no .geo

    - É necessário desalocar a memória utilizada pelo retono de todas as funções desse módulo

    - Todas as funções assumem command != NULL
*/

/*
    # Entrada:
        command: Instrução do .geo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna uma string contendo o tipo da forma em command

        - c -> circulo
        - r -> retangulo
        - l -> reta
        - t -> texto
*/
string getFormType(string command);

/*
    # Entrada:
        - command: Instrução do .geo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna uma string contendo o ID da forma indicada por command
*/
string getFormID(string command);

/*
    # Entrada:
        - command: Instrução do .geo
    
    # Saída
        - string
    
    # Descrição:
        - Retorna uma string contendo o ponto âncora da forma em command

        - Caso a forma seja uma linha, será retornada uma string contendo
          os dois pontos indicados em command, indicados por (x1, y1) e
          (x2, y2), respectivamente
*/
string getFormAnchor(string command);

/*
    # Entrada:
        - command: Instrução do .geo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna uma string contendo a(s) cor(es) da forma em command

        - Caso estejam indicadas mais de uma cor, elas serão retornadas em
          string na ordem em que aparecem em command
*/
string getFormColor(string command);

/*
    # Entrada:
        - command: Instrução do .geo
    
    # Saída:
        string
    
    # Descrição:
        - Retorna uma string contendo todas as informações da forma em command
*/
string reportForm(string command);

#endif