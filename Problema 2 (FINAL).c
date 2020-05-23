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

/*****
* TipoFunción: void ;NombreFunción: Sort
******
* Resumen Función
*Primero se recibe los parametros, a continuación se crea una variable llamada pivote la cual queda definida como el struct
*que queda en el medio de todo el arreglo, para luego dividir el problema en 2 partes, una parte que queda al lado izquierdo del 
*pivote y otro al lado derecho, para luego ir ordenando la parte izquierda, y luego la parte derecha, para luego al final chequear
*si esta bien ordenado con el primer sort desde el inicio a la derecha, y en el segundo sort de derecha a izquierda, para que
*finalmente salga de la función.
******
* Input:
* tipoParámetro: Cliente, int, int ;NombreParámetro: Recibe un arreglo tipo Cliente, el inicio del array, y el final.
******
* Returns:
* TipoRetorno: no retorna nada ;Descripción retorno: Ordena el arreglo para poder iterarlo en orden.
*****/

void actualizarSaldos(char *clientes, char *transacciones){
    FILE *fp=fopen(transacciones,"r");
    FILE *fc= fopen(clientes,"r+");

    if (fc == NULL){
        printf("No existe el archivo que nos indica: %s\n", clientes);
        exit (1);
    }

    if (fp == NULL){
        printf("No existe el archivo que nos indica: %s\n",transacciones);
        exit (1);
    }

    char Operacion;
    int Cuenta = 0, CuentaAux = 0 , Monto = 0 , Largo = 0;
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

    clienteBanco clientetext;
    int nclientes = 0,contador=0;
    while(fread(&clientetext, sizeof(clienteBanco), 1, fc)){
        if(clientetext.nroCuenta==cliente1[nclientes].nCuenta){
            clientetext.saldo+=cliente1[nclientes].nMonto;
            fseek(fc,ftell(fc)-sizeof(clienteBanco),0);
            fwrite(&clientetext,sizeof(clienteBanco),1,fc);
            nclientes++;
        }
        contador++;
    }

    free((void*)cliente1);
    fclose(fc);
}

/*****
* TipoFunción: void ;NombreFunción: actualizarSaldos
******
* Resumen Función
*Lo primero que se abre el archivo de texto transacciones y el de clientes para verificar si estos existen, y si no
*detener la ejecución del programa, a continuación iteramos el archivo transacciones para ir guardando las transacciones
*que se van a realizar, ya sea deposito, retiro y transacción de una cuenta a otra, luego una vez las tengamos todas, 
*necesitamos ordenarlas para iterar a la par al momento ir leyendo el archivo de los clientes y modificando su saldo.
*Finalmente se lee el archivo binario de clientes y se va modificando el saldo si este tiene: deposito o retiro, ya que
*anteriormente separarmos los depositos en 2, restandole al que deposita, y aumentandole al que recibe, así solo sumamos
*al momento de modificar su saldo, para y finalmente cerrar el archivo ya modificado.
******
* Input:
* tipoParámetro: char, char ;NombreParámetro: 2 cadenas de caracteres con el nombre de los archivos a abrir.
******
* Returns:
* TipoRetorno: no retorna nada ;Descripción retorno: Realiza la actualización de el saldo en el archivo binario de clientes.
*****/

int main(){
    char *varClientes = (char*)malloc(sizeof(char));
    char *varTransacciones = (char*)malloc(sizeof(char));

    printf("Ingrese el nombre del archivo de clientes(incluyendo su extension):");
    scanf("%s", varClientes);

    printf("Ingrese el nombre del archivo de transacciones(incluyendo su extension):");
    scanf("%s", varTransacciones);

    actualizarSaldos(varClientes, varTransacciones);

    free((void*)varClientes);
    free((void*)varTransacciones);
    return 0;
}

/*****
* TipoFunción: int ;NombreFunción: main
******
* Resumen Función
*Es el que nos permite ejecutar el programa, para hacer funcionar las demás funciones las cuales invocaremos.
******
* Input: 
* tipoParámetra:  ;NombreParámetro: no recibe parametros, ya que es el que permite la ejecución del programa completo.
******
* Returns:
* TipoRetorno: retorna el entero 0 ;Descripción retorno: el fin de ejecución del programa 
*****/
