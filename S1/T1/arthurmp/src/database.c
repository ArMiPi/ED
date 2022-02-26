#include<stdio.h>
#include<stdlib.h>

#include"database.h"

typedef struct _database {
    string name;
    queue data;
}DATABASE;

/*
    # Entrada:
        - fullpath: path completo para o arquivo a ser aberto
    
    # Saída:
        - FILE*: Ponteiro para FILE

    # Descrição:
        - Abre o arquivo fullpath para leitura
        
        - O programa será finalizado caso não seja possível
          abrir o arquivo
*/
FILE *openFile(string fullpath) {
    FILE *fptr = fopen(fullpath, "r");
    if(fptr == NULL) {
        printf("ERROR: Could not open %s\n", fullpath);
        exit(EXIT_FAILURE);
    }

    return fptr;
}

/*
    # Saída:
        - DATABASE: Struct
    
    # Descrição:
        - Retorna um DATABASE vazio
*/
DATABASE *newDatabase() {
    DATABASE *db = (DATABASE *) malloc(sizeof(DATABASE));
    if(db == NULL) {
        printf("ERROR: Could not allocate memory for new database\n");
        exit(EXIT_FAILURE);
    }

    db->name = NULL;
    db->data = NULL;

    return db;
}

database readData(string path, string name) {
    if(path == NULL || name == NULL) return NULL;

    string fullpath;
    if(endsWith(path, "/")) fullpath = concat(path, name);
    else {
        string barPath = concat(path, "/");
        fullpath = concat(barPath, name);
        free(barPath);
    }

    FILE *fptr = openFile(fullpath);

    // Criar DATABASE
    DATABASE *db = newDatabase();
    db->name = fullpath;

    return db;
}

string getDBname(database db) {
    if(db == NULL) return NULL;

    DATABASE *DB = (DATABASE *) db;

    return DB->name;
}