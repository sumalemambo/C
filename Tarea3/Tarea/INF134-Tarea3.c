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
    hashP HT;
    producto aux1;
    oferta aux2;
    hashO HT2;
    binTree T;
    heap h3;


    fread(&n,sizeof(int),1,fp);
    if( n == 0 ){
        printf("No hay productos que agregar\n");
        exit(1);
    }

    initTree(&T);
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

    fscanf(fc,"%d\n",&n);
    fscanf(fc,"%d\n",&clientes);

    while(clientes != 0){

        fscanf(fc,"%d\n",&cliente);
        while(cliente != 0){
            fscanf(fc,"%d\n",&key);
            insert(&T,key,&size);
            cliente--;
        }
        treeAc(&T,&HT,&HT2);
        clientes--;
    }
    fclose(fc);
    //PreOrder2(&T);

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
    
    dato aux;
    while(n != 1){
        aux = deleteMax(&h3);
        fprintf(rank,"%d %s %d %d\n",aux.key,hashSearch(&HT,aux.key)->nombre_producto,aux.rep, aux.value);
        n--;
    }
    aux = deleteMax(&h3);
    fprintf(rank,"%d %s %d %d",aux.key,hashSearch(&HT,aux.key)->nombre_producto,aux.rep, aux.value);
    fclose(rank);

    clearHashp(&HT);
    clearTree(&T);
    free((void*)array);
    return 0;
}