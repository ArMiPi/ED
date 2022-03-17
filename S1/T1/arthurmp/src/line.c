#include<stdio.h>
#include<stdlib.h>

#include"line.h"
#include"split.h"

#define MAX_SIZE 100

string lineEquation(string points) {
    if(points == NULL) return NULL;

    // Coeficiente linear da reta
    double m = lineM(points);

    // Cálculo dos valores de a e b
    Splited splt = split(points, " ");

    double x0 = strtod(getSubstring(splt, 0), NULL);
    double y0 = strtod(getSubstring(splt, 1), NULL);

    double a = 1 / m;
    double b = (-x0 / m) + y0;

    // Criar string com a equação da reta
    string temp = newEmptyString(MAX_SIZE);
    sprintf(temp, "y = %d x + %d", a, b);

    string equation = copyString(temp);

    free(temp);
    destroySplited(splt);

    return equation;
}

double lineM(string points) {
    if(points == NULL) return NULL;

    Splited splt = split(points, " ");

    double x0 = strtod(getSubstring(splt, 0), NULL);
    double y0 = strtod(getSubstring(splt, 1), NULL);
    double x = strtod(getSubstring(splt, 2), NULL);
    double y = strtod(getSubstring(splt, 3), NULL);

    return (x - x0) / (y - y0);
}

double lineX(string lineEquation, double y) {
    if(lineEquation == NULL || y == NULL) return 0.0;

    Splited splt = split(lineEquation, " ");

    double a = strtod(getSubstring(splt, 2), NULL);
    double b = strtod(getSubstring(splt, 5), NULL);

    return (y - b) / a;
}