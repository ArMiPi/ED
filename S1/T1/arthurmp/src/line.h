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
        - x0, y0, x1, y1: Coordenadas de pontos P0 e P1 pertencentes a uma reta
    
    # Saída:
        - double
    
    # Descrição:
        - Retorna o coeficiente angular da reta:
            m = (y1 - y0) / (x1 - x0)
*/
double lineM(double x0, double y0, double x1, double y1);

/*
    # Entradas:
        - x0, y0, x1, y1: Coordenadas de pontos P0 e P1 pertencentes a uma reta
        - y: Coordenada y delimitada por y0 e y1
    
    # Saídas:
        - double
    
    # Descrição:
        - Retorna o valor da coordenada x do ponto (x, y)
          pretencente à reta que contém os pontos (x0, y0) e (x1, y1)
*/
double lineX(double x0, double y0, double x1, double y1, double y);

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