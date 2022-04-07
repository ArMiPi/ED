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

    fprintf(txt, "[*] %s\n", command);
    if(toReport != NULL) fprintf(txt, "%s\n\n", toReport);
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
        if(selSize != -1 && selPlusSize != -1) {
            fprintf(txt, "Quantidade de itens antes da selecao: %d\n", selSize);
            fprintf(txt, "Quantidade de itens inseridos: %d\n", selPlusSize);
        }
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
    if(selSize != -1 && selPlusSize != -1) {
        fprintf(txt, "Quantidade de itens antes da selecao: %d\n", selSize);
        fprintf(txt, "Quantidade de itens inseridos: %d\n", selPlusSize);
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
        - id: Id inicial para a criação das retas
        - distance: Distância entre as retas
        - e: Espessura das linhas
        - color: Cor das linhas
        - lines: Lista contendo as coordenadas de cada linha
        - db: Lista onde as linhas serão inseridas
        - maxY: Maior valor de y do polígono
        - minY: Menor valor de y do polígono
    
    # Descrição:
        - Cria as linhas internas do polígono criado em pol

        - Todas as entradas devem ser != NULL
*/
void createInternalLines(int id, double distance, string e, string color, llist lines, llist db, double maxY, double minY) {
    if(lines == NULL || db == NULL) return;

    Splited coordinates;
    double x0, y0, x1, y1, x;
    double linePoints[2];
    int controller;
    string temp = newEmptyString(MAX_SIZE);
    string toInsert;

    // Criar retas a partir de minY até maxY espaçadas em distance
    for(double y = minY; y < maxY; y += distance) {
        controller = 0;
        // Verificar quais linhas de lines contém a coordenada y
        for(item li = GetFirstItem(lines); li != NULL; li = GetNextItem(li)) {
            coordinates = split((string) GetItemElement(li), " ");
            
            x0 = strtod(getSubstring(coordinates, 0), NULL);
            y0 = strtod(getSubstring(coordinates, 1), NULL);
            x1 = strtod(getSubstring(coordinates, 2), NULL);
            y1 = strtod(getSubstring(coordinates, 3), NULL);

            destroySplited(coordinates);

            // Verificar se y está presente nessa reta
            if(y0 > y1 && y > y0) continue;
            if(y0 > y1 && y < y1) continue;
            if(y1 > y0 && y > y1) continue;
            if(y1 > y0 && y < y0) continue;

            // Calcular valor da coordenada x do ponto (x, y) pertencente à reta
            x = lineX(x0, y0, x1, y1, y);

            linePoints[controller] = x;
            controller++;

            if(controller == 2) {
                if(linePoints[0] != linePoints[1]) {
                    sprintf(temp, "lp %d %lf %lf %lf %lf %s %s", id, linePoints[0], y, linePoints[1], y, color, e);
                    toInsert = copyString(temp);
                    InsertEnd(db, toInsert);
                }

                id++;
                controller = 0;
            }  
        }
    }

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
queue pol(string i, string d, string e, string corb, string corp, queue polygon, llist db) {
    if(polygon == NULL || db == NULL) return polygon;
    if(isQueueEmpty(polygon)) return polygon;

    // Valores utilizados para a criação das linhas no svg
    int id = atoi(i);

    // Fila auxiliar para manter os pontos após a criação do polígono
    queue aux = newQueue();

    // Lista contendo as retas que formam o polígono
    llist polLines = NewList();

    // Maiores / Menores coordenadas do polígono
    double maiorY, menorY, tempCoordinate;
    
    string temp = newEmptyString(MAX_SIZE);
    string current = (string) dequeue(polygon); 
    string next, toInsert;

    Splited spltP;
    spltP = split(current, " ");
    maiorY = strtod(getSubstring(spltP, 1), NULL);
    menorY = strtod(getSubstring(spltP, 1), NULL);

    destroySplited(spltP);

    // Inserir primeiro elemento removido de polygon em aux
    enqueue(aux, current);
    
    // Laço para as retas que formam a borda do polígono
    while(!isQueueEmpty(polygon)) {
        next = (string) dequeue(polygon);

        // Analisar coordenada
        spltP = split(next, " ");

        tempCoordinate = strtod(getSubstring(spltP, 1), NULL);
        if(tempCoordinate < menorY) menorY = tempCoordinate;
        if(tempCoordinate > maiorY) maiorY = tempCoordinate;

        destroySplited(spltP);

        // Criar comando das retas que formam o polígono
        sprintf(temp, "lp %d %s %s %s %s", id, current, next, corb, e);
        toInsert = copyString(temp);
        InsertEnd(db, toInsert);

        // Criar e armazenar os pontos para posterior criação das linhas de preenchimento
        sprintf(temp, "%s %s", current, next);
        toInsert = copyString(temp);
        InsertEnd(polLines, toInsert);

        // Inserir ponto que foi removido de polygon em aux
        enqueue(aux, next);

        // Informações para próxima interação
        id++;
        current = next;
    }
    // Inserir primeiro ponto de polygon novamente para "fechar" o polígono
    sprintf(temp, "lp %d %s %s %s %s", id, current, (string) peekQueue(aux), corb, e);
    toInsert = copyString(temp);
    InsertEnd(db, toInsert);
    // Inserir última linha
    sprintf(temp, "%s %s", current, (string) peekQueue(aux));
    toInsert = copyString(temp);
    InsertEnd(polLines, toInsert);

    free(temp);

    // Criar as retas internas do polígono
    int distancia = atoi(d);
    createInternalLines(id, distancia, e, corp, polLines, db, maiorY, menorY);

    DestroyList(polLines, NULL);
    destroyQueue(polygon, NULL);
    return aux;
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
llist sel(llist selected) {
    if(selected == NULL) return NewList();
    
    // Desconsiderar seleções anteriores
    while(!IsListEmpty(selected)) RemoveItem(selected, GetFirstItem(selected));
    DestroyList(selected, NULL);
    
    return NewList();
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
    string ring;
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
            if(!isLineInArea(points, area)) continue;
            
            InsertEnd(selected, li);

            // Criar anel ao redor do ponto de ancoragem
            ring = newEmptyString(MAX_SIZE);
            sprintf(ring, "c 0 %lf %lf 1.000 red red", x, y);
            InsertBefore(db, li, ring);
        }
        else if(strcmp(getFormType(command), "retangulo") == 0) {
            double x = strtod(getSubstring(splt, 2), NULL);
            double y = strtod(getSubstring(splt, 3), NULL);
            double w = strtod(getSubstring(splt, 4), NULL);
            double h = strtod(getSubstring(splt, 5), NULL);

            sprintf(points, "%lf %lf %lf %lf", x, y, x+w, y+h);
            if(!isLineInArea(points, area)) continue;
            
            InsertEnd(selected, li);

            // Criar anel ao redor do ponto de ancoragem
            ring = newEmptyString(MAX_SIZE);
            sprintf(ring, "c 0 %lf %lf 1.000 red red", x, y);
            InsertBefore(db, li, ring);
        }
        else if(strcmp(getFormType(command), "reta") == 0) {
            double x0 = strtod(getSubstring(splt, 2), NULL);
            double y0 = strtod(getSubstring(splt, 3), NULL);
            double x1 = strtod(getSubstring(splt, 4), NULL);
            double y1 = strtod(getSubstring(splt, 5), NULL);

            sprintf(points, "%lf %lf %lf %lf", x0, y0, x1, y1);
            if(!isLineInArea(points, area)) continue;
            
            InsertEnd(selected, li);

            // Criar anel ao redor do ponto de ancoragem
            ring = newEmptyString(MAX_SIZE);
            sprintf(ring, "c 0 %lf %lf 1.000 red red", x0, y0);
            InsertBefore(db, li, ring);
        }
        else if(strcmp(getFormType(command), "texto") == 0) {
            double x = strtod(getSubstring(splt, 2), NULL);
            double y = strtod(getSubstring(splt, 3), NULL);

            point P = newPoint(x, y);

            if(isPointInArea(P, area)) continue;
            
            InsertEnd(selected, li);

            // Criar anel ao redor do ponto de ancoragem
            ring = newEmptyString(MAX_SIZE);
            sprintf(ring, "c 0 %lf %lf 1.000 red red", x, y);
            InsertBefore(db, li, ring);
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

    fprintf(txt, "[*] dels\n");

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
    if(IsListEmpty(selected)) return;

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
void ups(string corb, string corp, string dx, string dy, string n, llist selected, llist db) {
    if(selected == NULL || db == NULL) return;
    if(IsListEmpty(selected)) return;
    if(ListSize(selected) == 1) return;

    int N = atoi(n);
    double DX = strtod(dx, NULL);
    double DY = strtod(dy, NULL);
    item pivot = GetItemElement(GetLastItem(selected)); // Última forma selecionada por sel

    string forma, toAdd, toRemove;
    Splited splt;
    if(N > 0) {
        for(int i = 1; i <= N; i++) {
            pivot = GetNextItem(pivot);
            if(pivot == NULL) return;
            forma = GetItemElement(pivot);
            splt = split(forma, " ");

            if(strcmp(getFormType(forma), "circulo") == 0) {
                string id = getSubstring(splt, 1);
                double x = strtod(getSubstring(splt, 2), NULL);
                double y = strtod(getSubstring(splt, 3), NULL);
                string r = getSubstring(splt, 4);

                x += DX;
                y += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "c %s %lf %lf %s %s %s", id, x, y, r, corb, corp);
            }
            else if(strcmp(getFormType(forma), "retangulo") == 0) {
                string id = getSubstring(splt, 1);
                double x = strtod(getSubstring(splt, 2), NULL);
                double y = strtod(getSubstring(splt, 3), NULL);
                string w = getSubstring(splt, 4);
                string h = getSubstring(splt, 5);

                x += DX;
                y += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "r %s %lf %lf %s %s %s %s", id, x, y, w, h, corb, corp);
            }
            else if(strcmp(getFormType(forma), "reta") == 0) {
                string id = getSubstring(splt, 1);
                double x0 = strtod(getSubstring(splt, 2), NULL);
                double y0 = strtod(getSubstring(splt, 3), NULL);
                double x1 = strtod(getSubstring(splt, 4), NULL);
                double y1 = strtod(getSubstring(splt, 5), NULL);

                x0 += DX;
                x1 += DX;
                y0 += DY;
                y1 += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "l %s %lf %lf %lf %lf %s", id, x0, y0, x1, y1, corb);
            }
            else if(strcmp(getFormType(forma), "texto") == 0) {
                string id = getSubstring(splt, 1);
                double x = strtod(getSubstring(splt, 2), NULL);
                double y = strtod(getSubstring(splt, 3), NULL);
                string a = getSubstring(splt, 6);
                string *content = getAllSubstrings(splt);
                content += 7;
                string txto = join((getNumSubstrings(splt) - 7), content, " ");
            
                x += DX;
                y += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "t %s %lf %lf %s %s %s %s", id, x, y, corb, corp, a, txto);

                free(txto);
            }

            toRemove = ReplaceItem(pivot, toAdd);

            free(toRemove);
            destroySplited(splt);
            DY++;
        }
    }
    else {
        for(int i = -1; i >= N; i--) {
            pivot = GetPreviousItem(pivot);
            if(pivot == NULL) return;
            forma = GetItemElement(pivot);
            splt = split(forma, " ");

            if(strcmp(getFormType(forma), "circulo") == 0) {
                string id = getSubstring(splt, 1);
                double x = strtod(getSubstring(splt, 2), NULL);
                double y = strtod(getSubstring(splt, 3), NULL);
                string r = getSubstring(splt, 4);

                x += DX;
                y += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "c %s %lf %lf %s %s %s", id, x, y, r, corb, corp);
            }
            else if(strcmp(getFormType(forma), "retangulo") == 0) {
                string id = getSubstring(splt, 1);
                double x = strtod(getSubstring(splt, 2), NULL);
                double y = strtod(getSubstring(splt, 3), NULL);
                string w = getSubstring(splt, 4);
                string h = getSubstring(splt, 5);

                x += DX;
                y += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "r %s %lf %lf %s %s %s %s", id, x, y, w, h, corb, corp);
            }
            else if(strcmp(getFormType(forma), "reta") == 0) {
                string id = getSubstring(splt, 1);
                double x0 = strtod(getSubstring(splt, 2), NULL);
                double y0 = strtod(getSubstring(splt, 3), NULL);
                double x1 = strtod(getSubstring(splt, 4), NULL);
                double y1 = strtod(getSubstring(splt, 5), NULL);

                x0 += DX;
                x1 += DX;
                y0 += DY;
                y1 += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "l %s %lf %lf %lf %lf %s", id, x0, y0, x1, y1, corb);
            }
            else if(strcmp(getFormType(forma), "texto") == 0) {
                string id = getSubstring(splt, 1);
                double x = strtod(getSubstring(splt, 2), NULL);
                double y = strtod(getSubstring(splt, 3), NULL);
                string a = getSubstring(splt, 6);
                string *content = getAllSubstrings(splt);
                content += 7;
                string txto = join((getNumSubstrings(splt) - 7), content, " ");
            
                x += DX;
                y += DY;

                toAdd = newEmptyString(MAX_SIZE);
                sprintf(toAdd, "t %s %lf %lf %s %s %s %s", id, x, y, corb, corp, a, txto);

                free(txto);
            }

            toRemove = ReplaceItem(pivot, toAdd);

            free(toRemove);
            destroySplited(splt);
            DY++;
        }
    }
}

void executeQry(string BSD, string geoName, string qryName, llist commands, llist database) {
    if(BSD == NULL || geoName == NULL || qryName == NULL || commands == NULL || database == NULL) return;
    

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
    
    // txt de saída utilizado por algumas qrys
    FILE *txt = createTXT(BSD, resultName);

    Splited splt;
    for(item i = GetFirstItem(commands); i != NULL; i = GetNextItem(i)) {
        splt = split((string)GetItemElement(i), " ");

        if(strcmp(getSubstring(splt, 0), "inp") == 0) {
            if(polygon == NULL) polygon = newQueue();

            toReport = inp(getSubstring(splt, 1), polygon, database);
            reportTXT(txt, GetItemElement(i), toReport);
        }
        else if(strcmp(getSubstring(splt, 0), "rmp") == 0) {
            toReport = rmp(polygon);
            reportTXT(txt, GetItemElement(i), toReport);
        }
        else if(strcmp(getSubstring(splt, 0), "pol") == 0) {
            polygon = pol(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), polygon, database);
            reportTXT(txt, GetItemElement(i), NULL);
        }
        else if(strcmp(getSubstring(splt, 0), "clp") == 0) {
            clp(polygon);
            reportTXT(txt, GetItemElement(i), NULL);
        }
        else if(strcmp(getSubstring(splt, 0), "sel") == 0) {
            if(selected == NULL) selected = NewList();

            selected = sel(selected);
            selplus(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), database, selected);

            reportSel(txt, GetFirstItem(selected), -1, -1, GetItemElement(i));
            selSize = ListSize(selected);
        }
        else if(strcmp(getSubstring(splt, 0), "sel+") == 0) {
            if(selected == NULL) selected = sel(selected);
            item first = GetLastItem(selected);

            selplus(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), database, selected);
            
            if(first == NULL) first = GetFirstItem(selected);
            else first = GetNextItem(first);
            reportSel(txt, first, selSize, ListSize(selected) - selSize, GetItemElement(i));
            selSize = ListSize(selected);
        }
        else if(strcmp(getSubstring(splt, 0), "dels") == 0) {
            dels(txt, selected, database);
            selSize = 0;
        }
        else if(strcmp(getSubstring(splt, 0), "dps") == 0) {
            dps(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), database, selected);
            reportTXT(txt, GetItemElement(i), NULL);
        }
        else if(strcmp(getSubstring(splt, 0), "ups") == 0) {
            ups(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), selected, database);
            reportTXT(txt, GetItemElement(i), NULL);
        }
        else printf("WARNING: %s is not a valid command\n", getSubstring(splt, 0));

        destroySplited(splt);
    }

    if(txt != NULL) fclose(txt);
    if(polygon != NULL) destroyQueue(polygon, free);
    if(selected != NULL) DestroyList(selected, NULL);

    // Criar o svg resultante das qrys
    generateSVG(BSD, resultName, database);

    free(resultName);
}