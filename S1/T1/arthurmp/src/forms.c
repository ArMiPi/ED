#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"forms.h"
#include"split.h"

string getFormType(string command) {
    if(command == NULL) return NULL;

    Splited splt = split(command, " ");
    string type = getSubstring(splt, 0);

    if(strcmp(type, "c") == 0) type = copyString("circulo");
    else if(strcmp(type, "r") == 0) type = copyString("retangulo");
    else if(strcmp(type, "l") == 0) type = copyString("reta");
    else if(strcmp(type, "t") == 0) type = copyString("texto");
    else {
        printf("WARNING: %s is not a valid form\n", type);
        type = NULL;
    }

    destroySplited(splt);

    return type;
}

string getFormID(string command) {
    if(command == NULL) return NULL;

    Splited splt = split(command, " ");

    string id = getSubstring(splt, 1);

    destroySplited(splt);

    return id;
}

string getFormAnchor(string command) {
    if(command == NULL) return NULL;

    Splited splt = split(command, " ");

    string type = getFormType(command);

    string *pontos;
    string anchor;
    if(strcmp(type, "reta") == 0) {
        pontos = (string *) malloc(4 * sizeof(string));

        pontos[0] = getSubstring(splt, 2);
        pontos[1] = getSubstring(splt, 3);
        pontos[2] = getSubstring(splt, 4);
        pontos[3] = getSubstring(splt, 5);

        anchor = join(4, pontos, " ");
    }
    else {
        pontos = (string *) malloc(2 * sizeof(string));

        pontos[0] = getSubstring(splt, 2);
        pontos[1] = getSubstring(splt, 3);

        anchor = join(2, pontos, " ");
    }

    free(type);
    free(pontos);
    destroySplited(splt);

    return anchor;
}

string getFormColor(string command) {
    if(command == NULL) return NULL;

    Splited splt = split(command, " ");

    string colors;
    string type = getFormType(command);

    if(strcmp(type, "reta") == 0) colors = copyString(getSubstring(splt, 6));
    else {
        string *cores = (string*) malloc(2 * sizeof(string));

        if(strcmp(type, "circulo") == 0) {
            cores[0] = getSubstring(splt, 5);
            cores[1] = getSubstring(splt, 6);
        }
        else if(strcmp(type, "retangulo") == 0) {
            cores[0] = getSubstring(splt, 6);
            cores[1] = getSubstring(splt, 7);
        }
        else {
            cores[0] = getSubstring(splt, 4);
            cores[1] = getSubstring(splt, 5);
        }

        colors = join(2, cores, " ");
        free(cores);
    }

    destroySplited(splt);
    free(type);

    return colors;
}