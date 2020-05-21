#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    typedef struct{
        int nCuenta;
        int Monto;
    }Cliente;

    Cliente *clientes=(Cliente*)malloc(sizeof(Cliente)*10000000);
    memset(clientes,'\0',sizeof(clientes));
    for(int i=0; i < 10;i++){
        if(clientes[i] == 0){

        }
    }
    free((void*)clientes);
    return 0;
}
