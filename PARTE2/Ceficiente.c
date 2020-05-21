#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Cliente(X) Cliente X = {.Activo=NULL}


int main(){
    typedef struct{
        int nCuenta;
        int nMonto;
        int Activo;
    }Cliente;

    FILE *fp=fopen("transacciones.txt","r");
    char Operacion,Salto;
    int Cuenta=0,CuentaAux=0;
    int Monto=0;
    int Largo=0;

    Cliente *clientes=(Cliente*)malloc(sizeof(Cliente)*10000000);
    while(fgets(&Operacion,2,fp)!=NULL){
        if(Operacion=='+'){
            fscanf(fp," %d %d",&Cuenta,&Monto);
            
            for(int i = 0; i < 10000000;i++){
                if(clientes[i].Activo==NULL){
                    clientes[i].Activo='1';
                    clientes[i].nCuenta=Cuenta;
                    clientes[i].nMonto=Monto;
                    Largo++;
                    break;
                }
                else if(clientes[i].nCuenta==Cuenta){
                    clientes[i].nMonto+=Monto;
                    break;
                }
            }
            fgets(&Salto,2,fp);
        }
        else if(Operacion=='-'){
            fscanf(fp," %d %d",&Cuenta,&Monto);

            for(int i = 0; i < 10000000;i++){
                if(clientes[i].Activo==NULL){
                    clientes[i].Activo='1';
                    clientes[i].nCuenta=Cuenta;
                    clientes[i].nMonto=(Monto*-1);
                    Largo++;
                    break;
                }
                else if(clientes[i].nCuenta==Cuenta){
                    clientes[i].nMonto-=Monto;
                    break;
                }
            }
            fgets(&Salto,2,fp);
        }
        /*else{
            fscanf(fp," %d %d %d",&Cuenta,&CuentaAux,&Monto);

            for(int i = 0; i < 10000000;i++){
                if(clientes[i].Activo==NULL){
                    clientes[i].Activo='1';
                    clientes[i].nCuenta=Cuenta;
                    clientes[i].nMonto=(Monto*-1);
                    Largo++;
                    break;
                }
                else if(clientes[i].nCuenta==Cuenta){
                    clientes[i].nMonto-=Monto;
                    break;
                }
            }
            for(int i = 0; i < 10000000;i++){
                if(clientes[i].Activo==NULL){
                    clientes[i].Activo='1';
                    clientes[i].nCuenta=CuentaAux;
                    clientes[i].nMonto=Monto;
                    Largo++;
                    break;
                }
                else if(clientes[i].nCuenta==CuentaAux){
                    clientes[i].nMonto+=Monto;
                    break;
                }
            }
            fgets(&Salto,2,fp);
        }*/

    }
    clientes=(Cliente*)realloc(clientes,sizeof(Cliente)*Largo);
    for(int i=0; i < Largo ; i++){
        printf("Numero de cuenta :%d  Monto final: %d\n",clientes[i].nCuenta,clientes[i].nMonto);
    }
    free((void*)clientes);
    fclose(fp);
    return 0;
}
