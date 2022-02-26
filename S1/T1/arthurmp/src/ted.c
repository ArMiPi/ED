#include<stdio.h>
#include<stdlib.h>

#include"params.h"
#include"strings.h"
#include"database.h"
#include"queue.h"

int main(int argc, char *argv[]) {
    // Leitura dos parâmetros de entrada do programa
    params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    database db = readData(getBED(prms), getGEO(prms));

    printf("%s\n", getDBname(db));

    queue q = getDBdata(db);
    string s;
    while (!isQueueEmpty(q)) {
        s = (string)dequeue(q);
        printf("%s\n", s);
        free(s);
    }

    destroyDB(db);
    destroyParams(prms);    
}