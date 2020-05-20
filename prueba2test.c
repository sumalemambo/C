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

    FILE *fc = fopen(clientes,"r");
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
    clienteBanco *cuentas = (clienteBanco *)malloc(sizeof(clienteBanco)*10000000);
    int nclientes;

    while(fread(&cliente, sizeof(clienteBanco), 1, fc)) //Coloca los structs con la informacion en el array cliente
    {
        //printf("Numero de cuenta: %d\n", cliente.nroCuenta);
        //printf("Saldo: %d\n", cliente.saldo);
        //printf("Nombre: %s\n", cliente.nbre);
        //printf("Direccion: %s\n", cliente.direccion);
        //printf("\n");
        cuentas[nclientes] = cliente;
        nclientes++;
    }
    cuentas = realloc(cuentas,sizeof(clienteBanco)*nclientes);
    /*for (int i = 0; i < nclientes; i++)  //Verificar archivos en el array de clientes
    {
        printf("Numero de cuenta: %d\n", cuentas[i].nroCuenta);
        printf("Saldo: %d\n", cuentas[i].saldo);
        printf("Nombre: %s\n", cuentas[i].nbre);
        printf("Direccion: %s\n", cuentas[i].direccion);
    }
    */
   char aux;
   while(aux != EOF){
       aux = fgetc(ft);
       if (aux == '+'){
           
       }
       if(aux == '-'){

       }
       if(aux == '>'){

       }
    printf("ENTRE\n");
   }

    fclose(fc);
    fclose(ft);
}

int main(){
    actualizarSaldos("clientes.txt", "transacciones.txt");
    return 0;
}
