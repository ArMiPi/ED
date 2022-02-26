#include<stdio.h>

#include"params.h"
#include"strings.h"
#include"database.h"
#include"queue.h"

int main(int argc, char *argv[]) {
    // Leitura dos parâmetros de entrada do programa
    params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    database db = readData(getBED(prms), getGEO(prms));

    printf("%s", getDBname(db));
}