#include<stdio.h>
#include<stdlib.h>

#include"params.h"
#include"strings.h"
#include"database.h"
#include"llist.h"

int main(int argc, char *argv[]) {
    // Leitura dos parâmetros de entrada do programa
    params prms = newParams(argc, argv);

    // Ler e armazenar informações do .geo
    database db = readData(getBED(prms), getGEO(prms));

    llist lst = getDBdata(db);
    item li = GetFirstItem(lst);
    while(li != NULL) {
        printf("%s\n", (string)GetItemElement(li));
        li = GetNextItem(li);
    }
    // Criar .svg a partir do .geo

    destroyDB(db);
    destroyParams(prms);    
}