#ifndef QRY_H
#define QRY_H

#include<stdio.h>

#include"llist.h"

/*
    - Esse módulo tem por objetivo implementar os comandos do .qry
*/

/*
    # Entradas:
        - commands: Lista contendo os comandos do .qry
        - database: Lista contendo os comandos do .geo
    
    # Descrição:
        - Realiza os comandos do .qry e gera os aquivos
          e gera os arquivos resultantes
*/
void executeQry(llist commands, llist database);

#endif