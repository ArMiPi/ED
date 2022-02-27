#ifndef LINE_H
#define LINE_H

#include"strings.h"
#include"point.h"

/*
    - Esse módulo tem por objetivo definir uma reta

    - As funções que recebem line como parâmetro de entrada assumem line != NULL
*/

typedef void *line;

/*
    # Entrada:
        - instruction: Comando do .geo para criar uma linha
    
    # Saída:
        - line: Struct
    
    # Descrição:
        - Retorna uma reta com base nas instruções em instruction
*/
line newLine(string instruction);

/*
    # Entrada:
        - l: Reta
    
    # Saída:
        - int
    
    # Descrição:
        - Retorna o id da reta
*/
int getLineID(line l);

/*
    # Entrada:
        - l: Reta
    
    # Saída:
        - point: Ponto
    
    # Descrição:
        - Retorna o ponto inicial da reta
*/
point getLineStartPoint(line l);

/*
    # Entrada:
        - l: Reta
    
    # Saída:
        - point: Ponto
    
    # Descrição:
        - Retorna o ponto final da reta
*/
point getLineEndPoint(line l);

/*
    # Entrada:
        - l: Reta
    
    # Saída:
        - string
    
    # Descrição:
        - Retorna a cor da reta
*/
string getLineColor(line l);

/*
    # Entrada:
        - l: Reta
    
    # Descrição:
        - Libera a memóra utilizada por l
*/
void destroyLine(line l);

#endif