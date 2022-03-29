#include<stdlib.h>
#include<string.h>

#include"qry.h"
#include"split.h"
#include"queue.h"
#include"point.h"
#include"forms.h"
#include"line.h"
#include"svg.h"

#define MAX_SIZE 100

/*
    # Entradas:
        - path: Path para a criação do arquivo
        - name: Nome do arquivo (sem extensão)
    
    # Saída:
        - FILE*: Ponteiro para arquivo
    
    # Descrição:
        - Abre um arquivo name.txt em path para
          escrita
*/
FILE *createTXT(string path, string name) {
    if(path == NULL || name == NULL) return NULL;

    // Gerar caminho completo para criação do arquivo
    string fullname = concat(name, ".txt");
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

    free(fullpath);

    return fptr;
}

/*
    # Entradas:
        - txt: Ponteiro para um arquivo .txt
        - command: String contendo um comando do .qry
        - toReport: String contendo o conteúdo a ser escrito no .txt
    
    # Descrição:
        - Escreve os conteúdos de command e toReport em txt
        - txt != NULL
*/
void reportTXT(FILE *txt, string command, string toReport) {
    if(txt == NULL) return;

    if(command == NULL) command = "NULL";
    if(toReport == NULL) toReport = "Nada a reportar\n\n";

    fprintf(txt, "[*] %s\n", command);
    fprintf(txt, "%s\n\n", toReport);
}

/*
    # Entrada:
        - txt: Ponteiro para um arquivo .txt
        - selected: Ponteiro para um elemento de selected
        - selSize: Tamanho de selected antes de um selplus
        - selPlusSize: Tamanho de selected após um selplus
        - command: Comando do .qry

    # Descrição:
        - Reporta em txt o comando command e todas as informações das formas em selected
          a partir do item indicado por selectedItem

        - Se selSize == -1 || selPlusSize == -1 os parâmetros não serão inseridos em txt

        - txt != NULL 
*/
void reportSel(FILE *txt, item selectedItem, int selSize, int selPlusSize, string command) {
    if(txt == NULL) return;

    if(selectedItem == NULL || command == NULL) {
        reportTXT(txt, command, NULL);
        return;
    }

    fprintf(txt, "[*] %s\n", command);

    item forma;
    string comandoForma;
    Splited splt;
    for(item li = selectedItem; li != NULL; li = GetNextItem(li)) {
        forma = GetItemElement(li);
        comandoForma = GetItemElement(forma);

        splt = split(comandoForma, " ");

        fprintf(txt, "%s %s\n", getSubstring(splt, 1), getFormType(comandoForma));
    
        destroySplited(splt);
    }
    fprintf(txt, "\n");
}

/*
    # Entradas:
        - command: Comando do .qry
        - i: Id de uma forma
        - polygon: Fila contendo as coordenadas do polígono atual
        - db: Lista contendo as formas do .geo
    
    # Saída:
        - string: String contendo todas as informações da forma

    # Descrição:
        - Insere em polygon a coordenada âncora da forma com
          id = i
        
        - Se a forma for uma reta, escolher o ponto com menor x,
          se ambas tiverem o mesmo valor para x, escolher a com
          o menor valor de y

        - Retorna a string a ser inserida no .txt
*/
string inp(string i, queue polygon, llist db) {
    if(polygon == NULL || db == NULL) return NULL;
    if(i == NULL) {
        printf("WARNING: Missing a parameter for inp\n");
        return NULL;
    }

    Splited splt;
    string coordinate;
    string toReport;
    // Percorrer db em busca do forma com id i
    for(item li = GetFirstItem(db); li != NULL; li = GetNextItem(li)) {
        splt = split(GetItemElement(li), " ");

        if(strcmp(getSubstring(splt, 1), i) != 0) {
            destroySplited(splt);
            continue;
        }

        // Armazenar o valor da coordenada âncora da forma encontrada
        if(strcmp(getFormType(GetItemElement(li)), "reta") == 0) {
            string temp = getFormAnchor(GetItemElement(li));
            Splited spltt = split(temp, " ");

            string points[2];
            points[0] = getSubstring(spltt, 0);
            points[1] = getSubstring(spltt, 1);

            coordinate = join(2, points, " ");

            free(temp);
            destroySplited(spltt);
        }
        else coordinate = getFormAnchor(GetItemElement(li));

        // Armazenar a coordenada encontrada em polygon
        enqueue(polygon, coordinate);
        toReport = reportForm(GetItemElement(li));

        destroySplited(splt);
        
        break;
    }

    return toReport;
}

/*
    # Entradas:
        - polygon: Fila contendo as coordenadas do polígono atual
    
    # Saída:
        - string: String contendo a coordenada removida

    # Descrição:
        - Remove a coordenada mais antiga inserida em polygon

        - Retorna a string a ser inserida no .txt
*/
string rmp(queue polygon) {
    if(polygon == NULL) return NULL;

    string toReport = dequeue(polygon);

    return toReport;
}

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
void pol(string i, string d, string e, string corb, string corp, queue polygon, llist db) {
    // Valores utilizados para a criação das linhas no svg
    int id = atoi(i);
    string cor = corb;

    // Lista contendo as retas que formam o polígono
    llist polLines = NewList();
    
    // Inserir as retas que formam o polígono em db
    string temp = newEmptyString(MAX_SIZE);
    string current = (string) dequeue(polygon);
    string first = copyString(current);
    string next, toInsert;
    
    // Laço para as retas que formam o polígono
    while(!isQueueEmpty(polygon)) {
        // Ponto final da reta
        next = (string) dequeue(polygon);
        if(next == NULL) next = first;

        // Criar comando das retas que formam o polígono
        sprintf(temp, "lp %d %s %s %s %s", id, current, next, cor, e);
        toInsert = copyString(temp);
        InsertEnd(db, toInsert);

        // Criar e armazenar equação da reta
        sprintf(temp, "%s %s", current, next);
        toInsert = copyString(temp);
        InsertEnd(polLines, toInsert);

        // Informações para próxima interação
        id++;
        free(current);
        current = next;
    }
    free(first);
    free(temp);
    destroyQueue(polygon, NULL);

    // Laço para as retas internas ao polígono

}

/*
    # Entrada:
        - polygon: Fila contendo as coordenadas do polígono atual
    
    # Descrição:
        - Remove todas as coordenadas do polígono corrente
*/
void clp(queue polygon) {
    if(polygon == NULL) return;

    while(!isQueueEmpty(polygon)) free(dequeue(polygon));
}

/*
    # Entradas:
        - x: Coordenada x do ponto de ancoragem da região
        - y: Coordenada y do ponto de ancoragem da região
        - w: Largura da região
        - h: Altura da região
        - db: Lista contendo as formas do .geo
        - selected: Lista para armazenar as formas selecionadas
    
    # Saída:
        - string: Comando para inserir a área no .svg

    # Descrição:
        - Seleciona as figuras INTEIRAMENTE dentro da região delimitada
        
        - selected armazena os itens contendo as formas selecionadas

        - Desconsidera seleções anteriores, ou seja, "esvazia" selected
*/
void sel(llist selected) {
    if(selected == NULL) return;
    
    // Desconsiderar seleções anteriores
    while(!IsListEmpty(selected)) RemoveItem(selected, GetFirstItem(selected));
    DestroyList(selected, NULL);
    selected = NewList();
}

/*
    # Entradas:
        - x: Coordenada x do ponto de ancoragem da região
        - y: Coordenada y do ponto de ancoragem da região
        - w: Largura da região
        - h: Altura da região
        - db: Lista contendo as formas do .geo
        - selected: Lista para armazenar as formas selecionadas
    
    # Saída:
        - string: Comando para inserir a área no .svg

    # Descrição:
        - Seleciona as figuras INTEIRAMENTE dentro da região delimitada
        
        - selected armazena os itens contendo as formas selecionadas
*/
void selplus(string x, string y, string w, string h, llist db, llist selected) {
    if(x == NULL || y == NULL || w == NULL || h == NULL || db == NULL) return;

    string temp[4];
    temp[0] = x;
    temp[1] = y;
    temp[2] = w;
    temp[3] = h;

    string area = join(4, temp, " ");
    string points = newEmptyString(MAX_SIZE);
    string command;
    Splited splt;
    // Procurar pelas formas contidas em area
    for(item li = GetFirstItem(db); li != NULL; li = GetNextItem(li)) {
        command = (string) GetItemElement(li);
        splt = split(command, " ");

        if(strcmp(getFormType(command), "circulo") == 0) {
            double x = strtod(getSubstring(splt, 2), NULL);
            double y = strtod(getSubstring(splt, 3), NULL);
            double r = strtod(getSubstring(splt, 4), NULL);

            sprintf(points, "%lf %lf %lf %lf", x-r, y, x+r, y);
            if(!isLineInArea(points, area)) continue;

            sprintf(points, "%lf %lf %lf %lf", x, y-r, x, y+r);
            if(isLineInArea(points, area)) InsertEnd(selected, li);
        }
        else if(strcmp(getFormType(command), "retangulo") == 0) {
            double x = strtod(getSubstring(splt, 2), NULL);
            double y = strtod(getSubstring(splt, 3), NULL);
            double w = strtod(getSubstring(splt, 4), NULL);
            double h = strtod(getSubstring(splt, 5), NULL);

            sprintf(points, "%lf %lf %lf %lf", x, y, x+w, y+h);
            if(isLineInArea(points, area)) InsertEnd(selected, li);
        }
        else if(strcmp(getFormType(command), "reta") == 0) {
            double x0 = strtod(getSubstring(splt, 2), NULL);
            double y0 = strtod(getSubstring(splt, 3), NULL);
            double x1 = strtod(getSubstring(splt, 4), NULL);
            double y1 = strtod(getSubstring(splt, 5), NULL);

            sprintf(points, "%lf %lf %lf %lf", x0, y0, x1, y1);
            if(isLineInArea(points, area)) InsertEnd(selected, li);
        }
        else if(strcmp(getFormType(command), "texto") == 0) {
            double x = strtod(getSubstring(splt, 2), NULL);
            double y = strtod(getSubstring(splt, 3), NULL);

            point P = newPoint(x, y);

            if(isPointInArea(P, area)) InsertEnd(selected, li);
        }

        destroySplited(splt);
    }

    // Criar comando para inserir a área no .svg
    string areaCmd = newEmptyString(MAX_SIZE);
    sprintf(areaCmd, "r 0 %s red white", area);
    InsertEnd(db, areaCmd);

    free(points);
    free(area);
}

/*
    # Entradas:
        - txt: Ponteiro para um arquivo.txt
        - selected: Lista com as formas selecionadas
        - db: Lista contendo as formas do .geo

    # Saída:
        - string: Reportar todos os dados das figuras removidas

    # Descrição:
        - Remove as figuras em selected de db

        - SVG: As figuras removidas não devem aparecer
*/
void dels(FILE *txt, llist selected, llist db) {
    if(txt == NULL || selected == NULL || db == NULL) return;

    fprintf(txt, "[*] del\n");

    item li;
    string forma, toReport;
    while(!IsListEmpty(selected)) {
        li = GetItemElement(GetFirstItem(selected));
        forma = GetItemElement(li);
        toReport = reportForm(forma);

        fprintf(txt, "%s\n", toReport);

        li = RemoveItem(selected, GetFirstItem(selected));
        RemoveItem(db, li);
        free(forma);
        free(toReport);
    }
    fprintf(txt, "\n");
}

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
void dps(string i, string dx, string dy, string corb, string corp, llist db, llist selected) {
    if(db == NULL || selected == NULL) return;

    int ID = atoi(i);
    double DX = strtod(dx, NULL);
    double DY = strtod(dy, NULL);

    item forma;
    string command, toInsert;
    Splited splt;
    for(item li = GetFirstItem(selected); li != NULL; li = GetNextItem(li)) {
        forma = GetItemElement(li);
        command = GetItemElement(forma);
        splt = split(command, " ");

        if(strcmp(getFormType(command), "circulo") == 0) {
            toInsert = newEmptyString(MAX_SIZE);

            sprintf(toInsert, "c %d %lf %lf %s %s %s", ID, strtod(getSubstring(splt, 2), NULL)+DX, strtod(getSubstring(splt, 3), NULL)+DY, getSubstring(splt, 4), corb, corp);

            InsertEnd(db, toInsert);
        }
        else if(strcmp(getFormType(command), "retangulo") == 0) {
            toInsert = newEmptyString(MAX_SIZE);

            sprintf(toInsert, "r %d %lf %lf %s %s %s %s", ID, strtod(getSubstring(splt, 2), NULL)+DX, strtod(getSubstring(splt, 3), NULL)+DY, getSubstring(splt, 4), getSubstring(splt, 5), corb, corp);

            InsertEnd(db, toInsert);
        }
        else if(strcmp(getFormType(command), "reta") == 0) {
            toInsert = newEmptyString(MAX_SIZE);

            sprintf(toInsert, "l %d %lf %lf %lf %lf %s", ID, strtod(getSubstring(splt, 2), NULL)+DX, strtod(getSubstring(splt, 3), NULL)+DY, strtod(getSubstring(splt, 4), NULL)+DX, strtod(getSubstring(splt, 5), NULL)+DY, corb);

            InsertEnd(db, toInsert);
        }
        else if(strcmp(getFormType(command), "texto") == 0) {
            toInsert = newEmptyString(MAX_SIZE);

            string *content = getAllSubstrings(splt);
            content += 7;
            string txto = join((getNumSubstrings(splt) - 7), content, " ");

            sprintf(toInsert, "t %d %lf %lf %s %s %s %s", ID, strtod(getSubstring(splt, 2), NULL)+DX, strtod(getSubstring(splt, 3), NULL)+DY, corb, corp, getSubstring(splt, 6), txto);

            InsertEnd(db, toInsert);
            free(txto);
        }

        destroySplited(splt);
        ID++;
    }
}

/*
    # Entradas:
        - corb: Cor de borda
        - corp: Cor de preenchimento
        - dx: Translação horizontal
        - dy: Translação vertical
        - selected: Lista com as formas selecionadas
    
    # Descrição:
        - Altera as cores e a posição das formas em selected

        - Transladar as mesmas formas em dx e dy

*/
void ups(string corb, string corp, string dx, string dy, llist selected) {
    
}

void executeQry(string BSD, string geoName, string qryName, llist commands, llist database) {
    if(BSD == NULL || geoName == NULL || qryName == NULL || commands == NULL || database == NULL) return;
    
    // txt de saída utilizado por algumas qrys
    FILE *txt = NULL;

    // String a ser inserida no .txt
    string toReport;

    /*
        - Lista de ponteiros para os itens contendo as formas
          indicadas pelo comando sel
    */
    llist selected = NULL;
    int selSize = 0;

    /*
        - Fila de strings contendo as coordenadas âncoras das formas
          indicadas no comando inp

        - Na string as coordendas serão x e y respectivamente e separadas
          por um espaço em branco
    */
    queue polygon = NULL;

    // Nome dos arquivos .txt e .svg resultantes da consulta
    Splited name = split(qryName, "/");
    string names[2];
    names[0] = geoName;
    names[1] = getSubstring(name, getNumSubstrings(name)-1);

    string resultName = join(2, names, "-");

    destroySplited(name);

    Splited splt;
    for(item i = GetFirstItem(commands); i != NULL; i = GetNextItem(i)) {
        splt = split((string)GetItemElement(i), " ");

        if(strcmp(getSubstring(splt, 0), "inp") == 0) {
            if(txt == NULL) createTXT(BSD, resultName);
            if(polygon == NULL) newQueue();

            toReport = inp(getSubstring(splt, 1), polygon, database);
            reportTXT(txt, GetItemElement(i), toReport);
        }
        /*else if(strcmp(getSubstring(splt, 0), "rmp") == 0) {
            toReport = rmp(polygon);
            reportTXT(txt, GetItemElement(i), toReport);
        }
        else if(strcmp(getSubstring(splt, 0), "pol") == 0) pol(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), polygon, database);
        else if(strcmp(getSubstring(splt, 0), "clp") == 0) clp(polygon);*/
        else if(strcmp(getSubstring(splt, 0), "sel") == 0) {
            if(txt == NULL) txt = createTXT(BSD, resultName);
            if(selected == NULL) selected = NewList();
            sel(selected);
            selplus(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), database, selected);
            
            reportSel(txt, GetFirstItem(selected), -1, -1, GetItemElement(i));
            selSize = ListSize(selected);
        }
        else if(strcmp(getSubstring(splt, 0), "selplus") == 0) {
            item first = GetLastItem(selected);

            selplus(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), database, selected);
            
            reportSel(txt, first, selSize, ListSize(selected) - selSize, GetItemElement(i));
            selSize = ListSize(selected);
        }
        else if(strcmp(getSubstring(splt, 0), "dels") == 0) dels(txt, selected, database);
        else if(strcmp(getSubstring(splt, 0), "dps") == 0) dps(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), database, selected);
        //else if(strcmp(getSubstring(splt, 0), "ups") == 0) ups(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), selected);
        //else printf("WARNING: %s is not a valid command\n", getSubstring(splt, 0));

        destroySplited(splt);
    }

    if(txt != NULL) fclose(txt);
    if(polygon != NULL) destroyQueue(polygon, free);
    if(selected != NULL) DestroyList(selected, NULL);

    // Criar o svg resultante das qrys
    generateSVG(BSD, resultName, database);
}