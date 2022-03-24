#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"forms.h"
#include"split.h"
#include"point.h"

#define MAX_SIZE 300

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
        double x1, y1, x2, y2;

        x1 = strtod(getSubstring(splt, 2), NULL);
        y1 = strtod(getSubstring(splt, 3), NULL);
        x2 = strtod(getSubstring(splt, 4), NULL);
        y2 = strtod(getSubstring(splt, 5), NULL);

        point P1 = newPoint(x1, y1);
        point P2 = newPoint(x2, y2);

        if(comparePoints(P1, P2) < 0) {
            pontos[0] = getSubstring(splt, 2);
            pontos[1] = getSubstring(splt, 3);
            pontos[2] = getSubstring(splt, 4);
            pontos[3] = getSubstring(splt, 5);
        }
        else {
            pontos[0] = getSubstring(splt, 4);
            pontos[1] = getSubstring(splt, 5);
            pontos[2] = getSubstring(splt, 2);
            pontos[3] = getSubstring(splt, 3);
        }

        anchor = join(4, pontos, " ");

        free(P1);
        free(P2);
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

string reportForm(string command) {
    if(command == NULL) return NULL;

    Splited splt = split(command, " ");

    string type = getFormType(command);
    string temp = newEmptyString(MAX_SIZE);
    string report;

    if(strcmp(type, "circulo") == 0) {
        string x = getSubstring(splt, 2);
        string y = getSubstring(splt, 3);
        string raio = getSubstring(splt, 4);
        string preenchimento = getSubstring(splt, 5);
        string borda = getSubstring(splt, 6);

        sprintf(temp, "%s\nâncora em {%s, %s}\nraio: %s\npreenchimento: %s\nborda: %s", type, x, y, raio, preenchimento, borda);
    }
    else if(strcmp(type, "retangulo") == 0) {
        string x = getSubstring(splt, 2);
        string y = getSubstring(splt, 3);
        string width = getSubstring(splt, 4);
        string height = getSubstring(splt, 5);
        string preenchimento = getSubstring(splt, 6);
        string borda = getSubstring(splt, 7);

        sprintf(temp, "%s\nâncora em {%s, %s}\nlargura: %s\naltura: %s\npreenchimento: %s\nborda: %s", type, x, y, width, height, preenchimento, borda);
    }
    else if(strcmp(type, "reta")) {
        point P1 = newPoint(strtod(getSubstring(splt, 2), NULL), strtod(getSubstring(splt, 3), NULL));
        point P2 = newPoint(strtod(getSubstring(splt, 4), NULL), strtod(getSubstring(splt, 5), NULL));
        string x, y;

        if(comparePoints(P1, P2) > 0) {
            x = getSubstring(splt, 2);
            y = getSubstring(splt, 3);
        }
        else {
            x = getSubstring(splt, 4);
            y = getSubstring(splt, 5);
        }

        free(P1);
        free(P2);

        string cor = getSubstring(splt, 6);

        sprintf(temp, "%s\nâncora em {%s, %s}\ncor: %s", type, x, y, cor);
    }
    else if(strcmp(type, "texto") == 0) {
        string x = getSubstring(splt, 2);
        string y = getSubstring(splt, 3);
        string borda = getSubstring(splt, 4);
        string preenchimento = getSubstring(splt, 5);
        string anchorPos = getSubstring(splt, 6);
        string *content = getAllSubstrings(splt);
        content += 7;
        string txto = join((getNumSubstrings(splt) - 7), content, " ");

        sprintf(temp, "%s\nâncora em {%s, %s}\nborda: %s\npreenchimento: %s\na: %s\ntexto: %s", type, x, y, borda, preenchimento, anchorPos, txto);
        
        free(txto);
    }

    report = copyString(temp);
    free(temp);
    destroySplited(splt);

    return report;
}