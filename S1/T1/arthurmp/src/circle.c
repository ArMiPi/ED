#include<stdio.h>
#include<stdlib.h>

#include"circle.h"
#include"split.h"

typedef struct _circle {
    int id;
    point anchor;
    double r;
    string corb;
    string corp;
}CIRCLE;

circle newCircle(string instruction) {
    if(instruction == NULL) return NULL;

    CIRCLE *circ = (CIRCLE *) malloc(sizeof(CIRCLE));
    if(circ == NULL) {
        printf("ERROR: Could not allocate memory for circle\n");
        ext(EXIT_FAILURE);
    }

    Splited splt = split(instruction, " ");

    circ->id = atoi(getSubstring(splt, 1));
    circ->anchor = newPoint(strtod(getSubstring(splt, 2), NULL), strtod(getSubstring(splt, 3), NULL));
    circ->r = strtod(getSubstring(splt, 4), NULL);
    circ->corb = copyString(getSubstring(splt, 5));
    circ->corp = copyString(getSubstring(splt, 6));

    destroySplited(splt);

    return circ;
}

int getCircleID(circle circ) {
    if(circ == NULL) return 0;

    CIRCLE *c = (CIRCLE *) circ;

    return c->id;
}

point getCircleAnchor(circle circ) {
    if(circ == NULL) return NULL;

    CIRCLE *c = (CIRCLE *) circ;

    return c->anchor;
}

double getCircleRadius(circle circ) {
    if(circ == NULL) return 0.0;

    CIRCLE *c = (CIRCLE *) circ;

    return c->r;
}

string getCircleBodyColor(circle circ) {
    if(circ == NULL) return NULL;

    CIRCLE *c = (CIRCLE *) circ;

    return c->corp;
}

string getCircleBorderColor(circle circ) {
    if(circ == NULL) return NULL;

    CIRCLE *c = (CIRCLE *) circ;

    return c->corb;
}

void destroyCircle(circle circ) {
    if(circ == NULL) return;

    CIRCLE *c = (CIRCLE *) circ;

    if(c->anchor != NULL) free(c->anchor);
    if(c->corp != NULL) free(c->corp);
    if(c->corb != NULL) free(c->corb);

    free(c);
    c = NULL;
    circ = NULL
}