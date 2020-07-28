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

    initTree(&T);

    fread(&n,sizeof(int),1,fp);
    initHash(&HT);

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

    /*for(int i = 0 ; i < HT.maxSize;i++){
        printf("%d %d %s\n",HT.table[i].codigo_producto,HT.table[i].precio,HT.table[i].nombre_producto);
        printf("--------------------------\n");
    }*/

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
    PreOrder2(&T);

    printf("%d\n",size);

    destroyStack(&S);
    clearHasho(&HT2);

    dato* array = (dato*)malloc(sizeof(dato)*(size+1));
    treeToArray(array,&T);
    buildHeap(&h3,array,size);
    maxHeapify(&h3);
    for(int i = 1 ; i <= h3.lenght ; i++){
        printf("%d %d %d\n",h3.array[i].key,h3.array[i].rep,h3.array[i].value);
    }
    printf("%d\n",deleteMax(&h3).value);
    printf("%d\n",deleteMax(&h3).value);
    printf("%d\n",deleteMax(&h3).value);
    clearTree(&T);
    free((void*)array);
    

    
    

    
        
    
    

    /*for(int i = 0; i < HT2.maxSize;i++){
        printf("%d %d %d\n",HT2.table[i].codigo_producto,HT2.table[i].cantidad_descuento,HT2.table[i].monto_descuento);
        printf("------------------ \n");
    }*/
    //Para el resto es una cola
    clearHashp(&HT);
    return 0;
}
