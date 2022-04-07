#include<stdio.h>
#include<stdlib.h>

#include"line.h"
#include"split.h"

#define MAX_SIZE 100

double lineM(double x0, double y0, double x1, double y1) {
    double dx = x1 - x0;
    double dy = y1 - y0;

    if(dx == 0) return 0.0;

    return dy/dx;
}

double lineX(double x0, double y0, double x1, double y1, double y) {
    double m = lineM(x0, y0, x1, y1);

    double x = y - y0;
    x /= m;
    x += x0;

    if(m == 0) x = x0;

    return x;
}

bool isLineInArea(string points, string area) {
    if(points == NULL || area == NULL) return false;

    Splited spltP = split(points, " ");
    // Valores da reta
    double x0 = strtod(getSubstring(spltP, 0), NULL);
    double y0 = strtod(getSubstring(spltP, 1), NULL);
    double x1 = strtod(getSubstring(spltP, 2), NULL);
    double y1 = strtod(getSubstring(spltP, 3), NULL);

    Splited spltA = split(area, " ");
    // Valores da área
    double x = strtod(getSubstring(spltA, 0), NULL);
    double y = strtod(getSubstring(spltA, 1), NULL);
    double w = strtod(getSubstring(spltA, 2), NULL);
    double h = strtod(getSubstring(spltA, 3), NULL);

    destroySplited(spltP);
    destroySplited(spltA);

    // Definir se a reta pertence à area
    if(x0 < x || x0 > x+w) return false;
    if(x1 < x || x1 > x+w) return false;
    if(y0 < y || y0 > y+h) return false;
    if(y1 < y || y1 > y+h) return false;

    return true;
}
