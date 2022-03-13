#include<stdio.h>
#include<stdlib.h>

#include"point.h"

typedef struct _point {
    double x;
    double y;
}POINT;

point newPoint(double x, double y) {
    POINT *p = (POINT *) malloc(sizeof(POINT));
    if(p == NULL) {
        printf("ERROR: Could not allocate memory for new point\n");
        exit(EXIT_FAILURE);
    }

    p->x = x;
    p->y = y;

    return p;
}

double getPointX(point p) {
    if(p == NULL) return 0.0;

    POINT *P = (POINT *) p;

    return P->x;
}

double getPointY(point p) {
    if(p == NULL) return 0.0;

    POINT *P = (POINT *) p;

    return P->y;
}

void updatePoint(point p, double x, double y) {
    if(p == NULL) return;

    POINT *P = (POINT *) p;

    P->x = x;
    P->y = y;
}

int comparePoints(point p1, point p2) {
    if(p1 == NULL || p2 == NULL) return 0;

    POINT *P1 = (POINT *) p1;
    POINT *P2 = (POINT *) p2;

    if(P1->x < P2->x) return -1;
    else if(P1->x == P2->x && P1->y < P2->y) return -1;
    else if(P1->x == P2->x && P1->y == P2->y) return 0;
    return 1;
}