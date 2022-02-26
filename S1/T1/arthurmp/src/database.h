#ifndef DATABASE_H
#define DATABASE_H

#include"strings.h"
#include"llist.h"

/*
    - Esse módulo tem por objetivo definir funções para ler e armazenar
      os comandos dos arquivos .geo . qry

    - Todas as funções que recebem database como entrada assumeme
      database != NULL
*/

typedef void* database;

/*
    # Entradas:
        - path: Path para o arquivo
        - name: Nome do arquivo (com extensão)
    
    # Saída:
        - database: Struct
    
    # Descrição:
        - Abre o arquivo em path/name, armazena os comandos
          contidos nesse arquivo e fecha o arquivo
        
        - path != NULL && name != NULL

        - É necessário liberar a memória utilizada pelo retorno dessa função
*/
database readData(string path, string name);

/*
    # Entrada:
        - db: Dados
    
    # Saída:
        - string: char*
    
    # Descrição:
        - Retorna o nome do arquivo(sem extensão) do qual
          os comandos armazenados em db foram lidos
*/
string getDBname(database db);

/*
    # Entrada:
        - db: Struct
    
    # Saída:
        - llist: Lista
    
    # Descrição:
        - Retorna uma lista contendo os comandos armazenados
          em db
*/
llist getDBdata(database db);

/*
    # Entrada:
        - db: Struct
    
    # Descrição:
        - Libera a memória utilizada por db
*/
void destroyDB(database db);

#endif