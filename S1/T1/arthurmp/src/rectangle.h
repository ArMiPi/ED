#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"strings.h"
#include"point.h"

/*
    - Esse módulo tem por objetivo definir um retângulo

    - Todas as funções que recebem rectangle como entrada assumem rectangle != NULL
*/

typedef void *rectangle;

/*
    # Entrada:
        - instruction: Instrução do .geo para criação de um retângulo
    
    # Saída:
        - rectangle: Struct
    
    # Descrição:
        - Retorna um rectangle com base nas instruções em instruction

        - instruction != NULL
*/
rectangle newRectangle(string instruction);

/*
    # Entrada:
        - rect: Retângulo
    
    # Saída:
        - int
    
    # Descrição:
        - Retorna o id de rect
*/
int getRectangleID(rectangle rect);

/*
    # Entrada:
        - rect: Retângulo
    
    # Saída:
        - point: Ponto
    
    # Descrição:
        - Retorna o ponto âncora de rect
*/
point getRectangleAnchor(rectangle rect);

/*
    # Entrada:
        - rect: Retângulo
    
    # Saída:
        - double
    
    # Descrição:
        - Retorna a largura de rect
*/
double getRectangleWidth(rectangle rect);

/*
    # Entrada:
        - rect: Retângulo
    
    # Saída:
        - double
    
    # Descrição:
        - Retorna a altura de rect
*/
double getRectangleHeight(rectangle rect);

/*
    # Entrada:
        - rect: Retângulo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a cor de preenchimento de rect
*/
string getRectangleBodyColor(rectangle rect);

/*
    # Entrada:
        - rect: Retângulo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a cor da borda de rect
*/
string getRectangleBorderColor(rectangle rect);

/*
    # Entrada:
        - rect: Retângulo
    
    # Descrição:
        - Libera a memória utilizada por rect
*/
void destroyRectangle(rectangle rect);

#endif