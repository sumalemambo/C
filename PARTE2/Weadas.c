#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
} clienteBanco;

typedef struct {
    char proceso;
    int Cuenta1;
    int Cuenta2;
    int Monto;
} transac;


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
        /*printf("Numero de cuenta: %d\n", cliente.nroCuenta);
        printf("Saldo: %d\n", cliente.saldo);
        printf("Nombre: %s\n", cliente.nbre);
        printf("Direccion: %s\n", cliente.direccion);
        printf("\n");*/
        cuentas[nclientes] = cliente;
        nclientes++;
    }
    cuentas = realloc(cuentas,sizeof(clienteBanco)*nclientes);
    for (int i = 0; i < nclientes; i++)  //Verificar archivos en el array de clientes
    {
       /*printf("Numero de cuenta: %d\n", cuentas[i].nroCuenta);
        printf("Saldo: %d\n", cuentas[i].saldo);
        printf("Nombre: %s\n", cuentas[i].nbre);
        printf("Direccion: %s\n", cuentas[i].direccion);*/
    }
    
   char aux;
   int CantTrans = 0;
   transac **T_trans= (transac**)malloc(sizeof(transac)*100000000);
   while(aux != EOF){
       int numc1,numc2, cant;
       aux = fgetc(ft);
       transac *trans = (transac*)malloc(sizeof(transac));
       if (aux == '+'){
            fscanf(ft, "%d %d", &trans->Cuenta1, &trans->Monto);
            trans->proceso = aux;
            printf("%ls %ls\n", &trans->Cuenta1, &trans->Monto);
            T_trans[CantTrans] = trans;
            CantTrans++;
       }
       else if(aux == '-'){           
           fscanf(ft, "%d %d", &trans->Cuenta1, &trans->Monto);
           trans->proceso = aux;
           printf("%ls %ls\n", &trans->Cuenta1, &trans->Monto);
           T_trans[CantTrans] = trans;
           CantTrans++;
       }
       else if(aux == '>'){
           fscanf(ft, "%d %d %d", &trans->Cuenta1,&trans->Cuenta2, &trans->Monto);
           trans->proceso = aux;
           printf("%ls %ls %ls\n", &trans->Cuenta1,&trans->Cuenta2, &trans->Monto);
           T_trans[CantTrans] = trans;
           CantTrans++;
       }
       else{
           printf("Operacion No Valida\n");
       }
        free((void*)trans);
   }
    T_trans = (transac**)realloc(T_trans,sizeof(transac)*CantTrans);
    fclose(fc);
    fclose(ft);
}

int main(){
    actualizarSaldos("clientes.txt", "transacciones.txt");
    return 0;
}
