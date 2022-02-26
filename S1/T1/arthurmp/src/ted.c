#include<stdio.h>
#include<stdlib.h>

#include"params.h"
#include"strings.h"
#include"database.h"
#include"llist.h"
#include"svg.h"

int main(int argc, char *argv[]) {
    // Leitura dos parâmetros de entrada do programa
    params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    database db = readData(getBED(prms), getGEO(prms));

    llist data = getDBdata(db);

    // Criar .svg a partir do .geo
    generateSVG(getBSD(prms), getDBname(db), data);

    destroyDB(db);
    destroyParams(prms);    
}