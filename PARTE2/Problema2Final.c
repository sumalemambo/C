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


void actualizarSaldos(char *clientes, char *transacciones){

    FILE *fp=fopen(transacciones,"r");
    char Operacion;
    int Cuenta = 0, CuentaAux = 0 , Monto = 0 , Largo = 0;

    if (fp == NULL){
        printf("No existe el archivo que nos indica: %s\n",transacciones);
        exit (1);
    }

    Cliente *cliente1=(Cliente*)calloc(10000000,sizeof(Cliente));
    while(fgets(&Operacion,2,fp)!=NULL){
        if(Operacion=='+'){
            fscanf(fp," %d %d ",&Cuenta,&Monto); //El fscanf con el espacio al final consume el salto de linea, fgets nunca toma el \n
            
            for(int i = 0; i < 10000000;i++){ //Iteracion dependiente del break revisar si se puede hacer mas rapido
                if(cliente1[i].Activo==0){
                    cliente1[i].Activo='1';
                    cliente1[i].nCuenta=Cuenta;
                    cliente1[i].nMonto=Monto;
                    Largo++;
                    break;
                }
                else if(cliente1[i].nCuenta==Cuenta){
                    cliente1[i].nMonto+=Monto;
                    break;
                }
            }
        }
        else if(Operacion=='-'){
            fscanf(fp," %d %d ",&Cuenta,&Monto);

            for(int i = 0; i < 10000000;i++){
                if(cliente1[i].Activo==0){
                    cliente1[i].Activo='1';
                    cliente1[i].nCuenta=Cuenta;
                    cliente1[i].nMonto=(Monto*-1);
                    Largo++;
                    break;
                }
                else if(cliente1[i].nCuenta==Cuenta){
                    cliente1[i].nMonto-=Monto;
                    break;
                }
            }
        }
        else{
            fscanf(fp," %d %d %d ",&Cuenta,&CuentaAux,&Monto);
            for(int i = 0; i < 10000000;i++){
                if(cliente1[i].Activo==0){
                    cliente1[i].Activo='1';
                    cliente1[i].nCuenta=Cuenta;
                    cliente1[i].nMonto=(Monto*-1);
                    Largo++;
                    break;
                }
                else if(cliente1[i].nCuenta==Cuenta){
                    cliente1[i].nMonto-=Monto;
                    break;
                }
            }
            for(int i = 0; i < 10000000;i++){
                if(cliente1[i].Activo==0){
                    cliente1[i].Activo='1';
                    cliente1[i].nCuenta=CuentaAux;
                    cliente1[i].nMonto=Monto;
                    Largo++;
                    break;
                }
                else if(cliente1[i].nCuenta==CuentaAux){
                    cliente1[i].nMonto+=Monto;
                    break;
                }
            }
        }

    }

    cliente1=(Cliente*)realloc(cliente1,sizeof(Cliente)*Largo);
    fclose(fp);

    /*Aqui comienza el sort del arreglo de structs*/
    Sort(cliente1,0,Largo-1);
    /*Listo , ya ordena el arreglo*/

    fp= fopen(clientes,"r+");

    if (fp == NULL){
        printf("No existe el archivo que nos indica: %s\n", clientes);
        exit (1);
    }

    clienteBanco clientetext;
    int nclientes = 0,contador=0;

    while(fread(&clientetext, sizeof(clienteBanco), 1, fp)){
        fseek(fp,((contador+1)*sizeof(clienteBanco)),contador*sizeof(clienteBanco));
        if(clientetext.nroCuenta==cliente1[nclientes].nCuenta){
            clientetext.saldo+=cliente1[nclientes].nMonto;
            nclientes++;
        }
        printf("Numero de cuenta: %d\n", clientetext.nroCuenta);
        printf("Saldo: %d\n", clientetext.saldo);
        contador++;
    }

    free((void*)cliente1);
    fclose(fp);
}

int main(){
    actualizarSaldos("clientes.txt", "transacciones.txt");
    return 0;
}
