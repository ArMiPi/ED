#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"database.h"

#define MAX_SIZE 200

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

queue readFile(FILE *fptr) {
    queue q = newQueue();

    string line = newEmptyString(MAX_SIZE);
    string data;
    while (fgets(line, MAX_SIZE, fptr)) {
        data = copyString(line);
        if(data[strlen(data) - 1] == '\n') data[strlen(data) - 1] = '\0';
        enqueue(q, data);
    }
    
    free(line);

    return q;
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

    // Abrir arquivo para leitura
    FILE *fptr = openFile(fullpath);

    // Criar DATABASE
    DATABASE *db = newDatabase();
    db->name = slice(name, 0, strlen(name) - 5);
    db->data = readFile(fptr);

    // Fechar arquivo
    fclose(fptr);

    free(fullpath);

    return db;
}

string getDBname(database db) {
    if(db == NULL) return NULL;

    DATABASE *DB = (DATABASE *) db;

    return DB->name;
}

queue getDBdata(database db) {
    if(db == NULL) return NULL;

    DATABASE *DB = (DATABASE *) db;

    return DB->data;
}

void destroyDB(database db) {
    if(db == NULL) return;

    DATABASE *DB = (DATABASE *) db;

    if(DB->name) free(DB->name);
    if(DB->data != NULL) destroyQueue(DB->data, &free);
    free(DB);

    DB = NULL;
    db = NULL;
}