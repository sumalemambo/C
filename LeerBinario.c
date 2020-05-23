#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
}clienteBanco;
int main(){
    clienteBanco senor;
    FILE *fp=fopen("clientes.txt","r");
    while(fread(&senor,sizeof(clienteBanco),1,fp)){
        printf("%d\n %d\n %s\n %s\n",senor.nroCuenta,senor.saldo,senor.nbre,senor.direccion);
    }
    fclose(fp);
    return 0;
}
