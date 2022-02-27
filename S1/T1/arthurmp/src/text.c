#include<stdio.h>
#include<stdlib.h>

#include"text.h"
#include"split.h"

typedef struct _text {
    int id;
    point anchor;
    string corb;
    string corp;
    string a;
    string txto;
}TEXT;

text newText(string instruction) {
    if(instruction == NULL) return NULL;

    TEXT *txt = (TEXT *) malloc(sizeof(TEXT));
    if(txt == NULL) {
        printf("ERROR: Could not allocate memory for text\n");
        exit(EXIT_FAILURE);
    }

    Splited splt = split(instruction, " ");

    txt->id = atoi(getSubstring(splt, 1));
    txt->anchor = newPoint(strtod(getSubstring(splt, 2), NULL), strtod(getSubstring(splt, 3), NULL));
    txt->corb = copyString(getSubstring(splt, 4));
    txt->corp = copyString(getSubstring(splt, 5));
    txt->a = copyString(getSubstring(splt, 6));
    string *txto = getAllSubstrings(splt);
    txto += 7;
    txt->txto = join(getNumSubstrings(splt) - 7, txto, " ");

    free(splt);

    return txt;
}

int getTextID(text txt) {
    if(txt == NULL) return 0;

    TEXT *t = (TEXT *) txt;

    return t->id;
}

point getTextAnchor(text txt) {
    if(txt == NULL) return NULL;

    TEXT *t = (TEXT *) txt;

    return t->anchor;
}

string getTextBorderColor(text txt) {
    if(txt == NULL) return NULL;

    TEXT *t = (TEXT *) txt;

    return t->corb;
}

string getTextBodyColor(text txt) {
    if(txt == NULL) return NULL;

    TEXT *t = (TEXT *) txt;

    return t->corp;
}

string getTextA(text txt) {
    if(txt == NULL) return NULL;

    TEXT *t = (TEXT *) txt;

    return t->a;
}

string getTextTxto(text txt) {
    if(txt == NULL) return NULL;

    TEXT *t = (TEXT *) txt;

    return t->txto;
}

void destroyText(text txt) {
    if(txt == NULL) return;

    TEXT *t = (TEXT *) txt;

    if(t->anchor != NULL) free(t->anchor);
    if(t->corb != NULL) free(t->corb);
    if(t->corp != NULL) free(t->corp);
    if(t->a != NULL) free(t->a);
    if(t->txto != NULL) free(t->txto);

    free(t);
    t = NULL;
    txt = NULL;
}