#include <stdio.h>
#include <stdlib.h>




typedef struct {
    int nCuenta;
    int nMonto;
    char Activo;
}Cliente;

typedef struct {
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
}clienteBanco;





void Sort(Cliente *ListaClientes,int Inicio,int Final){

    int Pivote=ListaClientes[(Inicio+Final)/2].nCuenta;
    int izquierda=Inicio,derecha=Final;
    Cliente temporal;

    if(izquierda<=derecha){
    
        while(ListaClientes[izquierda].nCuenta< Pivote && izquierda<Final){
            izquierda++;
        }
        
        while(ListaClientes[derecha].nCuenta>Pivote){
            derecha--;
        }

        if(izquierda <= derecha){

            temporal=ListaClientes[izquierda];
            ListaClientes[izquierda]=ListaClientes[derecha];
            ListaClientes[derecha]=temporal;
            izquierda++;
            derecha--;
        }

        Sort(ListaClientes,Inicio,derecha);
        Sort(ListaClientes,izquierda,Final);
    }


}






int main(){

    FILE *fp=fopen("transacciones.txt","r");
    char Operacion;
    int Cuenta = 0, CuentaAux = 0 , Monto = 0 , Largo = 0;

    Cliente *clientes=(Cliente*)calloc(10000000,sizeof(Cliente));
    while(fgets(&Operacion,2,fp)!=NULL){
        if(Operacion=='+'){
            fscanf(fp," %d %d ",&Cuenta,&Monto); //El fscanf con el espacio al final consume el salto de linea, fgets nunca toma el \n
            
            for(int i = 0; i < 10000000;i++){ //Iteracion dependiente del break revisar si se puede hacer mas rapido
                if(clientes[i].Activo==0){
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
                if(clientes[i].Activo==0){
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
                if(clientes[i].Activo==0){
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
                if(clientes[i].Activo==0){
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
    fclose(fp);

    /*Aqui comienza el sort del arreglo de structs*/
    Sort(clientes,0,Largo-1);
    for(int i=0; i < Largo;i++){
        printf("%d %d\n",clientes[i].nCuenta,clientes[i].nMonto);
    }
    /*Listo , ya ordena el arreglo*/



    
    /*Desde aqui abrir el binario y modificar, IDEA: Crear una variable temporal del tipo clienteBanco, el struct ya esta definido
    ,leer un clienteBanco del binario y guardarlo en la temporal, revisar si su nCuenta coincide con el primer elemento del arreglo
    clientes, si coincide modificar el monto de clienteBanco SUMANDO SIEMPRE el monto de clientes[i].nMonto, luego printear sobre esa misma linea
    el nuevo clienteBanco, seguir iterando hasta el final del archivo, el arreglo clientes YA ESTA ORDENADO es decir va en el mismo orden que el
    binario de cuentas, si un nCuenta no coincide con la linea del archivo saltarlo inmediatamente porque eso significa que no esta en el arreglo*/





    free((void*)clientes);
    return 0;
}
