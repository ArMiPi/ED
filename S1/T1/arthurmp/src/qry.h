#ifndef QRY_H
#define QRY_H

#include<stdio.h>

#include"llist.h"
#include"strings.h"

/*
    - Esse módulo tem por objetivo implementar os comandos do .qry
*/

/*
    # Entradas:
        - BSD: Diretório base de saída
        - geoName: Nome do arquivo .geo de formas
        - qryName: Nome do arquivo .qry
        - commands: Lista contendo os comandos do .qry
        - database: Lista contendo os comandos do .geo
    
    # Descrição:
        - Realiza os comandos do .qry e gera os aquivos
          e gera os arquivos resultantes
*/
void executeQry(string BSD, string geoName, string qryName, llist commands, llist database);

#endif