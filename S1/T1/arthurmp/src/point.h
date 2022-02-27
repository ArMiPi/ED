#ifndef POINT_H
#define POINT_H

/*
    - Esse módulo tem por objetivo definir um ponto cartesiano

    - Todas as funções com point como entrada assumem point != NULL
*/

typedef void *point;

/*
    # Entradas:
        - x, y: Coordenadas do ponto
    
    # Saída:
        - point: Struct
    
    # Descrição:
        - Retorna um ponto com as coordenadas
          (x, y)

        - É necessário desalocar o retorno dessa função
          usando free()
*/
point newPoint(double x, double y);

/*
    # Entrada:
        - p: Ponto
    
    # Saída:
        - x: double
    
    # Descrição:
        - Retorna a coordenada x de p
*/
double getPointX(point p);

/*
    # Entrada:
        - p: Ponto
    
    # Saída:
        - y: double
    
    # Descrição:
        - Retorna a coordenada y de p
*/
double getPointY(point p);

/*
    # Entradas:
        - p: Ponto
        - x: Nova coordenada x
        - y: Nova coordenada y
    
    # Descrição:
        - Atualiza as coordenadas de p para (x, y)
*/
void updatePoint(point p, double x, double y);

#endif