#include<stdlib.h>

#include"qry.h"
#include"split.h"
#include"queue.h"
#include"strings.h"
#include"point.h"
#include"forms.h"

// selected deve ser uma lista onde cada elemento é um ponteiro para um elemento de db

/*
    # Entradas:
        - i: Id de uma forma
        - polygon: Fila contendo as coordenadas do polígono atual
        - db: Lista contendo as formas do .geo
        - txt: Ponteiro para um arquivo .txt
    
    # Descrição:
        - Insere em polygon a coordenada âncora da forma com
          id = i
        
        - Se a forma for uma reta, escolher o ponto com menor x,
          se ambas tiverem o mesmo valor para x, escolher a com
          o menor valor de y

        - TXT: Reportar a coordenada inserida e os dados da figura
*/
void inp(string i, queue polygon, llist db, FILE *txt) {
    if(i == NULL) {
        printf("WARNING: Missing a parameter for inp\n");
        return NULL;
    }

    Splited splt;
    point p;
    double x, y;
    // Percorrer db em busca do forma com id i
    for(item li = GetFirstItem(db); li != NULL; li = GetNextItem(li)) {
        splt = split(GetItemElement(li), " ");

        if(strcmp(getSubstring(splt, 1), i) != 0) {
            destroySplited(splt);
            continue;
        }

        // Armazenar o valor da coordenada âncora da forma encontrada
        string points = getFormAnchor(GetItemElement(li));
        Splited spltP = split(points, " ");

        x = strtod(getSubstring(spltP, 0), NULL);
        y = strtod(getSubstring(spltP, 1), NULL);

        p = newPoint(x, y);

        // Caso a forma seja uma reta
        if(getNumSubstrings(spltP) > 2) {
            double x2, y2;

            x2 = strtod(getSubstring(spltP, 2), NULL);
            y2 = strtod(getSubstring(spltP, 3), NULL);

            point P2 = newPoint(x2, y2);

            if(comparePoints(p, P2) > 0) free(P2);
            else {
                free(p);
                p = P2;
            }
        }

        // Armazenar a coordenada encontrada em polygon
        enqueue(polygon, p);

        free(points);
        destroySplited(splt);
        destroySplited(spltP);
        return;
    }
}

/*
    # Entradas:
        - polygon: Fila contendo as coordenadas do polígono atual
        - db: Lista contendo as formas do .geo
    
    # Descrição:
        - Remove a coordenada mais antiga inserida em polygon

        - TXT: Reportar a coordenada removida
*/
void rmp(queue polygon, llist db);

/*
    # Entradas:
        - i: Id inicial das linhas
        - d: Distância entre as linhas de preenchimento
        - e: Espessura das linhas
        - corb: Cor das linhas que formam o polígono
        - corp: Cor das linhas de preenchimento
        - polygon: Fila contendo as coordenadas do polígono atual
        - db: Lista contendo as formas do .geo

    # Descrição:
        - Produz um conjunto de linhas e os insere em db

        - As linhas produzidas representam as linhas da borda do polígono e as linhas de
          preenchimento do polígono
        
        - Os ids das linhas são sequenciais e iniciam em i

        - As linhas de preenchimento são separadas por uma distância vertical de d
*/
void pol(string i, string d, string e, string corb, string corp, queue polygon, llist db);

/*
    # Entrada:
        - polygon: Fila contendo as coordenadas do polígono atual
    
    # Descrição:
        - Remove todas as coordenadas do polígono corrente
*/
void clp(queue polygon);

/*
    # Entradas:
        - x: Coordenada x do ponto de ancoragem da região
        - y: Coordenada y do ponto de ancoragem da região
        - w: Largura da região
        - h: Altura da região
        - db: Lista contendo as formas do .geo
        - selected: Lista para armazenar as formas selecionadas
        - txt: Ponteiro para um arquivo .txt
    
    # Descrição:
        - Seleciona as figuras INTEIRAMENTE dentro da região delimitada

        - SVG: Desenhar a região
               Desenhar um anel vermelho ao redor da coordenada âncora das figuras
               selecionadas
        
        - TXT: Reportar id e tipo das figuras selecionadas
*/
void sel(string x, string y, string w, string h, llist db, llist selected, FILE *txt);

/*
    # Entradas:
        - selected: Lista com as formas selecionadas
        - txt: Ponteiro para um arquivo .txt

    # Descrição:
        - Remove as figuras em selected de db

        - SVG: As figuras removidas não devem aparecer

        - TXT: Reportar todos os dados das figuras removidas
*/
void dels(llist selected, FILE *txt);

/*
    # Entradas:
        - i: Id inicial
        - dx: Translação horizontal
        - dy: Translação vertical
        - corb: Cor de borda
        - corp: Cor de preenchimento
        - db: Lista contendo as formas do .geo
        - selected: Lista com as formas selecionadas

    # Descrição:
        - Criar novas formas em db semelhantes às em selected, transladadas em dx e dy, com
          as cores indicadas e id sequencial iniciado em i 
*/
void dps(string i, string dx, string dy, string corb, string corp, llist db, llist selected);

/*
    # Entradas:
        - corb: Cor de borda
        - corp: Cor de preenchimento
        - dx: Translação horizontal
        - dy: Translação vertical
        - selected: Lista com as formas selecionadas
    
    # Descrição:
        - Altera as cores e a posiçãodas formas em selected

        - Transladar as mesmas formas em dx e dy

*/
void ups(string corb, string corp, string dx, string dy, llist selected);

void executeQry(llist commands, llist database) {
    // txt de saída utilizado por algumas qrys
    FILE *txt = NULL;

    // Lista de formas selecionadas pelo comando sel
    llist selected = NULL;

    // Fila de pontos para a criação de um polígono (Pontos adicionados pela função inp)
    queue polygon = NULL;

    Splited splt;
    for(item i = GetFirstItem(commands); i != NULL; i = GetNextItem(i)) {
        splt = split((char *)GetItemElement(i), " ");

        if(strcmp(getSubstring(splt, 0), "inp") == 0) inp(getSubstring(splt, 1), polygon, database, txt);
        else if(strcmp(getSubstring(splt, 0), "rmp") == 0) rmp(polygon, database);
        else if(strcmp(getSubstring(splt, 0), "pol") == 0) pol(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), polygon, database);
        else if(strcmp(getSubstring(splt, 0), "clp") == 0) clp(polygon);
        else if(strcmp(getSubstring(splt, 0), "sel") == 0) sel(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), database, selected, txt);
        else if(strcmp(getSubstring(splt, 0), "dels") == 0) dels(selected, txt);
        else if(strcmp(getSubstring(splt, 0), "dps") == 0) dps(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), database, selected);
        else if(strcmp(getSubstring(splt, 0), "ups") == 0) ups(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), selected);
        else printf("WARNING: %s is not a valid comand\n", getSubstring(splt, 0));

        destroySplited(splt);
    }

    // Criar o svg resultante das qrys
    
}