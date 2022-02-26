#include<stdio.h>

#include"params.h"

int main(int argc, char *argv[]) {
    // Leitura dos parâmetros de entrada do programa
    params prms = newParams(argc, argv);

    if(getBED(prms) != NULL) printf("BED: %s\n", getBED(prms));
    if(getGEO(prms) != NULL) printf("GEO: %s\n", getGEO(prms));
    if(getBSD(prms) != NULL) printf("BSD: %s\n", getBSD(prms));
    if(getQRY(prms) != NULL) printf("QRY: %s\n", getQRY(prms));

    
    destroyParams(prms);
}