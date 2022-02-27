#include<stdio.h>
#include<stdlib.h>

#include"line.h"
#include"split.h"

typedef struct _line {
    int id;
    point p1, p2;
    string cor;
}LINE;

line newLine(string instruction) {
    if(instruction == NULL) return NULL;

    LINE *l = (LINE *) malloc(sizeof(LINE));
    if(l == NULL) {
        printf("ERROR: Could not allocate memory for line\n");
        exit(EXIT_FAILURE);
    }

    Splited splt = split(instruction, " ");

    l->id = atoi(getSubstring(splt, 1));
    l->p1 = newPoint(strtod(getSubstring(splt, 2), NULL), strtod(getSubstring(splt, 3), NULL));
    l->p2 = newPoint(strtod(getSubstring(splt, 4), NULL), strtod(getSubstring(splt, 5), NULL));
    l->cor = copyString(getSubstring(splt, 6));

    destroySplited(splt);

    return l;
}

int getLineID(line l) {
    if(l == NULL) return 0;

    LINE *L = (LINE *) l;

    return L->id;
}

point getLineStartPoint(line l) {
    if(l == NULL) return NULL;

    LINE *L = (LINE *) l;

    return L->p1;
}

point getLineEndPoint(line l) {
    if(l == NULL) return NULL;

    LINE *L = (LINE *) l;

    return L->p2;
}

string getLineColor(line l) {
    if(l == NULL) return NULL;

    LINE *L = (LINE *) l;

    return L->cor;
}

void destroyLine(line l) {
    if(l == NULL) return;

    LINE *L = (LINE *) l;

    if(L->p1 != NULL) free(L->p1);
    if(L->p2 != NULL) free(L->p2);
    if(L->cor != NULL) free(L->cor);

    free(l);
    l = NULL;
    L = NULL;
}