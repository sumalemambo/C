#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(){
    typedef struct{
        int nCuenta;
        int nMonto;
        char Activo;
    }Cliente;

    FILE *fp=fopen("transacciones.txt","r");
    char Operacion;
    int Cuenta = 0, CuentaAux = 0 , Monto = 0 , Largo = 0;

    Cliente *clientes=(Cliente*)malloc(sizeof(Cliente)*10000000);
    while(fgets(&Operacion,2,fp)!=NULL){
        if(Operacion=='+'){
            fscanf(fp," %d %d ",&Cuenta,&Monto); //El fscanf con el espacio al final consume el salto de linea, fgets nunca toma el \n
            
            for(int i = 0; i < 10000000;i++){ //Iteracion dependiente del break revisar si se puede hacer mas rapido
                if(clientes[i].Activo=='\0'){
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
        }
        else if(Operacion=='-'){
            fscanf(fp," %d %d ",&Cuenta,&Monto);

            for(int i = 0; i < 10000000;i++){
                if(clientes[i].Activo=='\0'){
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
        }
        else{
            fscanf(fp," %d %d %d ",&Cuenta,&CuentaAux,&Monto);
            for(int i = 0; i < 10000000;i++){
                if(clientes[i].Activo=='\0'){
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
                if(clientes[i].Activo=='\0'){
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
        }

    }
    clientes=(Cliente*)realloc(clientes,sizeof(Cliente)*Largo);
    for(int i=0; i < Largo ; i++){
        printf("Numero de cuenta :%d  Monto final: %d\n",clientes[i].nCuenta,clientes[i].nMonto);
    }
    fclose(fp);
    /*Aqui comenzar el sort del arreglo de structs usando el nCuenta*/


    /*Desde aqui abrir el binario y modificar*/
    
    free((void*)clientes);
    return 0;
}
