#ifndef CIRCLE_H
#define CIRCLE_H

#include"strings.h"
#include"point.h"

/*
    - Esse módulo tem por objetivo definir um círculo

    - Todas as funções que tem circle como entrada assumem circle != NULL
*/

typedef void *circle;

/*
    # Entrada:
        - instruction: Instrução do .geo para criar um círculo
    
    # Saída:
        - circle: Ponteiro
    
    # Descrição:
        - Retorna um circle com base nas informações em instruction

        - instruction != NULL
*/
circle newCircle(string instruction);

/*
    # Entrada:
        - circ: Círculo
    
    # Saída:
        - int
    
    # Descrição:
        - Retorna o id de circ
*/
int getCircleID(circle circ);

/*
    # Entrada:
        - circ: Círculo
    
    # Saída:
        - point: Ponto
    
    # Descrição:
        - Retorna o ponto âncora de circ
*/
point getCircleAnchor(circle circ);

/*
    # Entrada:
        - circ: Círculo
    
    # Saída:
        - double
    
    # Descrição:
        - Retorna o raio de circ
*/
double getCircleRadius(circle circ);

/*
    # Entrada:
        - circ: Círculo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a cor de preenchimento de circ
*/
string getCircleBodyColor(circle circ);

/*
    # Entrada:
        - circ: Círculo
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a cor da borda de circ
*/
string getCircleBorderColor(circle circ);

/*
    # Entrada:
        - circ: Círculo
    
    # Descrição:
        - Libera a memória utilizada por circ
*/
void destroyCircle(circle circ);

#endif