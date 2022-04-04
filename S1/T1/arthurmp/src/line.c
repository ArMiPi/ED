#include<stdio.h>
#include<stdlib.h>

#include"line.h"
#include"split.h"

#define MAX_SIZE 100

double lineM(string points) {
    if(points == NULL) return 0.0;

    Splited splt = split(points, " ");

    double x0 = strtod(getSubstring(splt, 0), NULL);
    double y0 = strtod(getSubstring(splt, 1), NULL);
    double x = strtod(getSubstring(splt, 2), NULL);
    double y = strtod(getSubstring(splt, 3), NULL);

    return (x - x0) / (y - y0);
}

double lineX(string lineEquation, double y) {
    if(lineEquation == NULL) return 0.0;

    Splited splt = split(lineEquation, " ");

    double a = strtod(getSubstring(splt, 2), NULL);
    double b = strtod(getSubstring(splt, 5), NULL);

    return (y - b) / a;
}

bool isLineInArea(string points, string area) {
    if(points == NULL || area == NULL) return false;

    Splited spltP = split(points, " ");
    Splited spltA = split(area, " ");

    // Valores da reta
    double x0 = strtod(getSubstring(spltP, 0), NULL);
    double y0 = strtod(getSubstring(spltP, 1), NULL);
    double x1 = strtod(getSubstring(spltP, 2), NULL);
    double y1 = strtod(getSubstring(spltP, 3), NULL);

    // Valores da área
    double x = strtod(getSubstring(spltA, 0), NULL);
    double y = strtod(getSubstring(spltA, 1), NULL);
    double w = strtod(getSubstring(spltA, 2), NULL);
    double h = strtod(getSubstring(spltA, 3), NULL);

    // Definir se a reta pertence à area
    if(x0 < x || x0 > x+w) return false;
    if(x1 < x || x1 > x+w) return false;
    if(y0 < y || y0 > y+h) return false;
    if(y1 < y || y1 > y+h) return false;

    return true;
}
