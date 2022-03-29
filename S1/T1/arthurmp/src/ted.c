#include<stdio.h>
#include<stdlib.h>

#include"params.h"
#include"strings.h"
#include"database.h"
#include"llist.h"
#include"svg.h"
#include"qry.h"

int main(int argc, char *argv[]) {
    // Leitura dos parâmetros de entrada do programa
    params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    database geo = readData(getBED(prms), getGEO(prms));

    // Criar .svg a partir do .geo
    generateSVG(getBSD(prms), getDBname(geo), getDBdata(geo));

    if(getQRY(prms) != NULL) {
        // Ler e armazenar informações do .qry
        database qry = readData(getBED(prms), getQRY(prms));

        // Executar comandos do .qry
        executeQry(getBSD(prms), getDBname(geo), getDBname(qry), getDBdata(qry), getDBdata(geo));

        destroyDB(qry);
    }

    destroyDB(geo);
    destroyParams(prms);    
}