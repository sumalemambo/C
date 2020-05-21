#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
} clienteBanco;

void cambioSaldo(clienteBanco *cliente, int cantidad);
void transferencia(clienteBanco *cliente1, clienteBanco *cliente2, int cantidad);

void actualizarSaldos(char *clientes, char *transacciones){

    FILE *fc = fopen(clientes,"r+");
    FILE *ft = fopen(transacciones,"r");

    if (fc == NULL){
        printf("No se pudo abrir el archivo: %s\n",clientes);
        exit (1);
    }

    if (ft == NULL){
        printf("No se pudo abrir el archivo: %s\n", transacciones);
        exit (1);
    }
    
    clienteBanco cliente;
    int nclientes;
    char aux;

    while(aux != EOF){
        int numc1,numc2, cant;
        aux = fgetc(ft);
        if (aux == '+'){
            fscanf(ft, "%d %d", &numc1, &cant);
            printf("%d %d\n", numc1, cant);
        }
        else if(aux == '-'){           
            fscanf(ft, "%d %d", &numc1, &cant);
            printf("%d %d\n", numc1, cant);
        }
        else{
            fscanf(ft, "%d %d %d", &numc1,&numc2, &cant);
            printf("%d %d %d\n", numc1, numc2, cant);
        }
        aux = fgetc(ft);
        aux = fgetc(ft);
    }
    
    fclose(fc);
    fclose(ft);


}

int main(){
    actualizarSaldos("clientes.txt", "transacciones.txt");
    return 0;
}
