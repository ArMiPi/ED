#include<stdlib.h>

#include"qry.h"
#include"split.h"
#include"queue.h"
#include"point.h"
#include"forms.h"

// selected deve ser uma lista onde cada elemento é um ponteiro para um elemento de db

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
    # Entradas:
        - command: Comando do .qry
        - i: Id de uma forma
        - polygon: Fila contendo as coordenadas do polígono atual
        - db: Lista contendo as formas do .geo
        - txt: Ponteiro para um arquivo .txt
    
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
        coordinate = getFormAnchor(GetItemElement(li));

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

void executeQry(string BSD, string geoName, string qryName, llist commands, llist database) {
    if(BSD == NULL || geoName == NULL || qryName == NULL || commands == NULL || database == NULL) return NULL;
    
    // txt de saída utilizado por algumas qrys
    FILE *txt = NULL;
    // String a ser inserida no .txt
    string toReport;

    // Lista de formas selecionadas pelo comando sel
    llist selected = NULL;

    /*
        - Fila de strings contendo as coordenadas âncoras das formas
          indicadas no comando inp

        - Na string as coordendas serão x e y respectivamente e separadas
          por um espaço em branco
    */
    queue polygon = NULL;

    // Nome dos arquivos .txt e .svg resultantes da consulta
    string *names;
    names[0] = geoName;
    names[1] = qryName;

    string resultName = join(2, names, "-");

    Splited splt;
    for(item i = GetFirstItem(commands); i != NULL; i = GetNextItem(i)) {
        splt = split((char *)GetItemElement(i), " ");

        if(strcmp(getSubstring(splt, 0), "inp") == 0) {
            if(txt == NULL) createTXT(BSD, resultName);
            if(polygon == NULL) newQueue();

            toReport = inp(getSubstring(splt, 1), polygon, database);
            reportTXT(txt, GetItemElement(i), toReport);
        }
        else if(strcmp(getSubstring(splt, 0), "rmp") == 0) {
            toReport = rmp(polygon);
            reportTXT(txt, GetItemElement(i), toReport);
        }
        else if(strcmp(getSubstring(splt, 0), "pol") == 0) pol(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), polygon, database);
        else if(strcmp(getSubstring(splt, 0), "clp") == 0) clp(polygon);
        else if(strcmp(getSubstring(splt, 0), "sel") == 0) sel(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), database, selected, txt);
        else if(strcmp(getSubstring(splt, 0), "dels") == 0) dels(selected, txt);
        else if(strcmp(getSubstring(splt, 0), "dps") == 0) dps(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), getSubstring(splt, 5), database, selected);
        else if(strcmp(getSubstring(splt, 0), "ups") == 0) ups(getSubstring(splt, 1), getSubstring(splt, 2), getSubstring(splt, 3), getSubstring(splt, 4), selected);
        else printf("WARNING: %s is not a valid comand\n", getSubstring(splt, 0));

        destroySplited(splt);
    }
    if(txt != NULL) fclose(txt);
    if(polygon != NULL) destroyQueue(polygon, free);

    // Criar o svg resultante das qrys
    
}