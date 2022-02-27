#include<stdio.h>
#include<stdlib.h>

#include"rectangle.h"
#include"split.h"

typedef struct _rectangle {
    int id;
    point anchor;
    double w;
    double h;
    string corb;
    string corp;
}RECTANGLE;

rectangle newRectangle(string instruction) {
    if(instruction == NULL) return NULL;

    RECTANGLE *rect = (RECTANGLE *) malloc(sizeof(RECTANGLE));
    if(rect == NULL) {
        printf("ERROR: Could not allocate memory for rectangle\n");
        exit(EXIT_FAILURE);
    }

    Splited splt = split(instruction, " ");

    rect->id = atoi(getSubstring(splt, 1));
    rect->anchor = newPoint(strtod(getSubstring(splt, 2), NULL), strtod(getSubstring(splt, 3), NULL));
    rect->w = strtod(getSubstring(splt, 4), NULL);
    rect->h = strtod(getSubstring(splt, 5), NULL);
    rect->corb = copyString(getSubstring(splt, 6));
    rect->corp = copyString(getSubstring(splt, 7));

    free(splt);

    return rect;
}

int getRectangleID(rectangle rect) {
    if(rect == NULL) return 0;

    RECTANGLE *r = (RECTANGLE *) rect;

    return r->id;
}

point getRectangleAnchor(rectangle rect) {
    if(rect == NULL) return NULL;

    RECTANGLE *r = (RECTANGLE *) rect;

    return r->anchor;
}

double getRectangleWidth(rectangle rect) {
    if(rect == NULL) return 0.0;

    RECTANGLE *r = (RECTANGLE *) rect;

    return r->w;
}

double getRectangleHeight(rectangle rect) {
    if(rect == NULL) return 0.0;

    RECTANGLE *r = (RECTANGLE *) rect;

    return r->h;
}

string getRectangleBodyColor(rectangle rect) {
    if(rect == NULL) return NULL;

    RECTANGLE *r = (RECTANGLE *) rect;

    return r->corp;
}

string getRectangleBorderColor(rectangle rect) {
    if(rect == NULL) return NULL;

    RECTANGLE *r = (RECTANGLE *) rect;

    return r->corb;
}

void destroyRectangle(rectangle rect) {
    if(rect == NULL) return;

    RECTANGLE *r = (RECTANGLE *) rect;

    if(r->anchor != NULL) free(r->anchor);
    if(r->corp != NULL) free(r->corp);
    if(r->corb != NULL) free(r->corp);

    free(r);
    r = NULL;
    rect = NULL;
}