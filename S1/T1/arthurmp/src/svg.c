#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILL_OPACITY "0.5"
#define FONT_SIZE "5"
#define LINE_HEIGHT "0"
#define STROKE_WIDTH "2"

#include"svg.h"
#include"split.h"

/*
    # Entradas:
        - path: Path para a criação do arquivo
        - name: Nome do arquivo (sem extensão)
    
    # Saída:
        - FILE*: Ponteiro para arquivo
    
    # Descrição:
        - Abre um arquivo name.svg em path para
          escrita
*/
FILE *createSVG(string path, string name) {
    // Gerar caminho completo para criação do arquivo
    string fullname = concat(name, ".svg");
    string fullpath;
    if(endsWith(path, "/")) fullpath = concat(path, fullname);
    else {
        string barPath = concat(path, "/");
        fullpath = concat(barPath, fullname);
        free(barPath);
    }
    free(fullname);

    FILE *fptr = fopen(fullpath, "w");
    if(fptr == NULL) printf("WARNING: Could not create %s\n", fullpath);

    if(fptr != NULL) {
        fprintf(fptr, "<svg xmlns:svg=\"http://www.w3.org/2000/svg\" xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\">\n");
    }

    free(fullpath);

    return fptr;
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Splited de um comando
    
    # Descrição:
        - Cria um cŕiculo em fptr com as informações em
          splt
*/
void drawCircle(FILE *fptr, Splited splt) {
    if(fptr == NULL || splt == NULL) return;

    string id = getSubstring(splt, 1);
    string x = getSubstring(splt, 2);
    string y = getSubstring(splt, 3);
    string r = getSubstring(splt, 4);
    string corb = getSubstring(splt, 5);
    string corp = getSubstring(splt, 6);

    fprintf(fptr, "<circle style=\"fill:%s; fill-opacity:%s; ", corp, FILL_OPACITY);
    fprintf(fptr, "stroke=%s;\" ", corb);
    fprintf(fptr, "r=\"%s\" ", r);
    fprintf(fptr, "cy=\"%s\" ", y);
    fprintf(fptr, "cx=\"%s\" />\n", x);

    fprintf(fptr, "<text style=\"font-size:%spx; line-height:%s%%; fill: %s\" ", FONT_SIZE, LINE_HEIGHT, corb);
    fprintf(fptr, "font-size=\"%s\" y=\"%s\" x=\"%s\" >", FONT_SIZE, y, x);
    fprintf(fptr, "%s </text>\n", id);
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Splited de um comando
    
    # Descrição:
        - Cria um retângulo em fptr com as informações em
          splt
*/
void drawRectangle(FILE *fptr, Splited splt) {
    if(fptr == NULL || splt == NULL) return;

    string id = getSubstring(splt, 1);
    string x = getSubstring(splt, 2);
    string y = getSubstring(splt, 3);
    string w = getSubstring(splt, 4);
    string h = getSubstring(splt, 5);
    string corb = getSubstring(splt, 6);
    string corp = getSubstring(splt, 7);

    fprintf(fptr, "<rect style=\"fill:%s; fill-opacity:%s; ", corp, FILL_OPACITY);
    fprintf(fptr, "stroke:%s\" ", corb);
    fprintf(fptr, "height=\"%s\" ", h);
    fprintf(fptr, "width=\"%s\" ", w);
    fprintf(fptr, "y=\"%s\" ", y);
    fprintf(fptr, "x=\"%s\" />\n", x);

    fprintf(fptr, "<text style=\"font-size:%spx; line-height:%s%%; fill: %s\" ", FONT_SIZE, LINE_HEIGHT, corb);
    fprintf(fptr, "font-size=\"%s\" y=\"%s\" x=\"%s\" >", FONT_SIZE, y, x);
    fprintf(fptr, "%s </text>\n", id);
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Splited de um comando
    
    # Descrição:
        - Cria uma reta em fptr com as informações em
          splt
*/
void drawLine(FILE *fptr, Splited splt) {
    if(fptr == NULL || splt == NULL) return;

    string id = getSubstring(splt, 1);
    string x1 = getSubstring(splt, 2);
    string y1 = getSubstring(splt, 3);
    string x2 = getSubstring(splt, 4);
    string y2 = getSubstring(splt, 5);
    string cor = getSubstring(splt, 6);

    fprintf(fptr, "<line x1=\"%s\" y1=\"%s\" ", x1, y1);
    fprintf(fptr, "x2=\"%s\" y2=\"%s\" ", x2, y2);
    fprintf(fptr, "style=\"stroke:%s; stroke-width:%s\" />\n", cor, STROKE_WIDTH);

    fprintf(fptr, "<text style=\"font-size:%spx; line-height:%s%%; fill: %s\" ", FONT_SIZE, LINE_HEIGHT, cor);
    fprintf(fptr, "font-size=\"%s\" y=\"%s\" x=\"%s\" >", FONT_SIZE, y1, x1);
    fprintf(fptr, "%s </text>\n", id);
}

/*
    # Entradas:
        - fptr: Ponteiro para arquivo de escrita
        - splt: Splited de um comando
    
    # Descrição:
        - Cria um texto em fptr com as informações em
          splt
*/
void drawText(FILE *fptr, Splited splt) {
    if(fptr == NULL || splt == NULL) return;

    string id = getSubstring(splt, 1);
    string x = getSubstring(splt, 2);
    string y = getSubstring(split, 3);
    string corb = getSubstring(splt, 4);
    string corp = getSubstring(splt, 5);
    string a = getSubstring(splt, 6);
    string *content = getAllSubStrings(splt);
    content += 6;
    string txto = join((getNumSubStrings(splt) - 6), content, " ");

    string anchor;
    if(strcmp(a, "i") == 0) anchor = "start";
    else if(strcmp(a, "m") == 0) anchor = "middle";
    else if(strcmp(a, "f") == 0) anchor = "end";

    fprintf(fptr, "<text text-anchor=\"%s\" x=\"%s\" y=\"%s\" ", anchor, x, y);
    fprintf(fptr, "style=\"fill:%s; fill-opacity:%s; ", corp, FILL_OPACITY);
    fprintf(fptr, "stroke:%s; stroke-width:%s;\"", corb, STROKE_WIDTH);
    fprintf(">%s</text>\n", txto);

    fprintf(fptr, "<text style=\"font-size:%spx; line-height:%s%%; fill: %s\" ", FONT_SIZE, LINE_HEIGHT, corb);
    fprintf(fptr, "font-size=\"%s\" y=\"%s\" x=\"%s\" >", FONT_SIZE, y, x);
    fprintf(fptr, "%s </text>\n", id);

    free(txto);
}

void generateSVG(string path, string name, llist data) {
    if(path == NULL || name == NULL || data == NULL) return;

    FILE *fptr = createSVG(path, name);
    if(fptr == NULL) return;

    Splited splt;
    for(item li = GetFirstItem(data); li != NULL; li = GetNextItem(li)) {
        splt = split((string )GetItemElement(li), " ");

        if(strcmp(getSubstring(splt, 0), "c") == 0)
            drawCircle(fptr, splt);
        if(strcmp(getSubstring(splt, 0), "r") == 0)
            drawRectangle(fptr, splt);
        if(strcmp(getSubstring(splt, 0), "l") == 0)
            drawLine(fptr, splt);
        if(strcmp(getSubstring(splt, 0), "t") == 0)
            drawText(fptr, splt);

        destroySplited(splt);
    }

    fprintf(fptr, "</svg>");

    fclose(fptr);
}