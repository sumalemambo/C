#include <stdlib.h>
#include <stdio.h>
#include "INF134-Hash.c"

int main(){
    FILE* fp=fopen("productos.dat","r");
    FILE* fo=fopen("ofertas.dat","r");
    FILE* fc=fopen("compras.txt","r");
    if(fp == NULL || fo == NULL || fc == NULL){
        printf("ERROR: Hubo un problema al abrir los archivos.\n");
        exit(1);
    }
    int n,clientes,cliente,key,size = 0;
    stack S;
    hashP HT;
    producto aux1;
    oferta aux2;
    hashO HT2;
    binTree T;
    dato aux;
    oferta* auxiliar;
    heap h3;

    fread(&n,sizeof(int),1,fp);
    if(n == 0){
        printf("No hay productos que agregar.\n");
        exit(1);
    }
    initHash(&HT);
    initTree(&T);

    while(n != 0){
        fread(&aux1,sizeof(producto),1,fp);
        hashInsert(&HT,aux1);
        if( (float)HT.size/HT.maxSize >= 0.7){
            rehash(&HT);
        }
        n--;
    }
    fclose(fp);

    initHashO(&HT2);
    fread(&n,sizeof(int),1,fo);

    while( n != 0 ){
        fread(&aux2,sizeof(oferta),1,fo);
        hashInsertO(&HT2,aux2);
        if( (float)HT2.size/HT2.maxSize >= 0.7){
            rehash2(&HT2);
        }
        n--;
    }
    fclose(fo);

    fscanf(fc,"%d\n",&n);
    fscanf(fc,"%d\n",&clientes);
    initStack(&S);

    while(clientes != 0){
        fscanf(fc,"%d\n",&cliente);
        while(cliente != 0){
            fscanf(fc,"%d\n",&key);
            if(lenght(&S) == 0){
                push(&S,key);
            }
            else{
                if(topValue(&S) != key){
                    aux.key = topValue(&S);
                    aux.rep = lenght(&S);
                    auxiliar = hashSearchO(&HT2,aux.key);
                    aux.value = hashSearch(&HT,aux.key)->precio * aux.rep - ((auxiliar == NULL)? 0 : (aux.rep / auxiliar->cantidad_descuento) * auxiliar->monto_descuento);
                    insert(&T,aux,&size);
                    clear(&S);
                }
                push(&S,key);
            }
            cliente--;
        }
        clientes--;
    }
    fclose(fc);

    aux.key = topValue(&S);
    aux.rep = lenght(&S);
    insert(&T,aux,&size);

    destroyStack(&S);
    clearHasho(&HT2);

    dato* array = (dato*)malloc(sizeof(dato)*(size+1));
    treeToArray(array,&T);
    buildHeap(&h3,array,size);
    maxHeapify(&h3);
    
    clearTree(&T);
    FILE* rank = fopen("ranking.txt","w");
    if(rank == NULL){
        printf("ERROR: Hubo un problema al abrir el archivo.\n");
        exit(1);
    }
    
    dato val;
    while(n-1 != 0){
        val = deleteMax(&h3);
        fprintf(rank,"%d %s %d %d\n",val.key,hashSearch(&HT,val.key)->nombre_producto,val.rep, val.value);
        n--;
    }
    fprintf(rank,"%d %s %d %d",val.key,hashSearch(&HT,val.key)->nombre_producto,val.rep, val.value);
    
    fclose(rank);
    clearHashp(&HT);
    free((void*)array);
    return 0;
}

/*****
* TipoFunción: int ;NombreFunción: main
******
* Resumen Función
*Primero se leen los archivos productos.dat, ofertas.dat y compras.txt, verificando primeramente si se pueden abrir o no,
*luego se definen variables las cuales se utilizaran para implementar todo el programa, primeramente se ingresan todos los
*productos a una tabla de hashing, y luego los de ofertas a otra tabla de hashing, posteriormente se comienza a leer el archivo
*de compras donde primero se saca el valor de la cantidad de productos que iran en el ranking, luego la cantidad de clientes,
*para luego ver las compras que hizo cada cliente ingresandolas a una pila, el cual se usara para ir contando la cantidad de
*elementos que se insertaran en el arbol con su repetición, despues limpiamos el stack para ir ingresando más nodos al arbol
*luego que se inserta todo al arbol se destruye el stack, luego se crea un arreglo donde iran los productos finalmente.
*La parte final es la de la escritura del archivo ranking.txt con el respectivo ranking.
******
* Input:
* tipoParámetra:    ;NombreParámetro:
******
* Returns:
* TipoRetorno: int ;Descripción retorno: Crea un ranking de los productos más comprados.
*****/
