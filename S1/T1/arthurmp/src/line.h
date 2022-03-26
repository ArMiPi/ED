#ifndef LINE_H
#define LINE_H

#include<stdbool.h>
#include"strings.h"

/*
    - Este módulo tem por objetivo fornecer funções específicas para
      retas
    
    - Todas as entradas das funções desse módulo devem ser != NULL
*/

/*
    # Entrada:
        - points: string contendo dois pontos pertencentes à reta
    
    # Saída:
        - string: y = a x + b
    
    # Descrição:
        - Retorna a equação da reta obtida a partir de:
            x - x0 = m(y - y0)
        
        - points deve conter as coordenadas x1 y1 x2 y2 respectivamente

        - Para a equação x0 = x1 e y0 = y1
*/
string lineEquation(string points);

/*
    # Entrada:
        - points: string contendo dois pontos pertencentes à reta
    
    # Saída:
        - string: Equação da reta
    
    # Descrição:
        - Retorna o coeficiente angular da reta:
            m = (x - x0) / (y - y0)
        
        - points deve conter as coordenadas x1 y1 x2 y2 respectivamente

        - Para a equação x0 = x1, y0 = y1, x = x2 e y = y2
*/
double lineM(string points);

/*
    # Entradas:
        - lineEq: string contendo a equação de uma reta
        - y: Coordenada y
    
    # Saídas:
        - double x
    
    # Descrição:
        - Retorna o valor da coordenada x do ponto (x, y)
          pretencente à reta lineEq
*/
double lineX(string lineEq, double y);

/*
    # Entradas:
        - points: string contendo contendo os pontos que delimitam a reta
        - area: string contendo os pontos que delimitam a área
    
    # Saída:
        - true/false
    
    # Descrição:
        - Retorna true caso a reta esterja totalmente contida em area,
          false caso contrário
        
        - points deve ser != NULL e deve apresentar as coordenadas na forma
          "x0 y0 x1 y1"
        
        - area deve ser != NULL e deve apresentar as coordenadas na forma
          "x y w h"
*/
bool isLineInArea(string points, string area);

#endif