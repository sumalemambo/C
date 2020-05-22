#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
}clienteBanco;

int main(){
    clienteBanco aux;
    FILE *fc = fopen("clientes.txt","w");

    aux.nroCuenta = 1;
    aux.saldo= 100;
    strcpy(aux.nbre,"Ignacio");
    strcpy(aux.direccion,"Fantasilandia");
    fwrite(&aux,sizeof(clienteBanco),1,fc);
    printf("%d\n",aux.nroCuenta);

    aux.nroCuenta = 2;
    aux.saldo= 1000;
    strcpy(aux.nbre,"Eduardo");
    strcpy(aux.direccion,"Fantasilandia");
    fwrite(&aux,sizeof(clienteBanco),1,fc);
    printf("%d\n",aux.nroCuenta);

    aux.nroCuenta = 3;
    aux.saldo= 1000;
    strcpy(aux.nbre,"Sebastian");
    strcpy(aux.direccion,"Fantasilandia");
    fwrite(&aux,sizeof(clienteBanco),1,fc);
    printf("%d\n",aux.nroCuenta);

    aux.nroCuenta = 4;
    aux.saldo= 1500;
    strcpy(aux.nbre,"Arroyuelo");
    strcpy(aux.direccion,"Fantasilandia");
    fwrite(&aux,sizeof(clienteBanco),1,fc);
    printf("%d\n",aux.nroCuenta);

    fclose(fc);


    return 0;
}
