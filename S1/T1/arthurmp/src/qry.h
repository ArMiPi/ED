#ifndef QRY_H
#define QRY_H

#include<stdio.h>

#include"queue.h"
#include"llist.h"
#include"strings.h"

/*
    - Esse módulo tem por objetivo implementar os comandos do .qry
*/

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
void inp(string i, queue polygon, llist db, FILE *txt);

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

#endif