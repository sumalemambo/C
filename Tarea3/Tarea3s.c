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

    int n;
    hashP HT;
    producto aux1;
    oferta aux2;
    hashO HT2;

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
    /*for(int i = 0 ; i < HT.maxSize;i++){
        printf("%d %d %s\n",HT.table[i].codigo_producto,HT.table[i].precio,HT.table[i].nombre_producto);
        printf("--------------------------\n");
    }*/

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

    heap H;
    elem arreglo[10];
    int auxiliar1;
    int auxiliar2;

    for(int i = 10;i--;){
        scanf("%d %d",&auxiliar1,&auxiliar2);
        arreglo[i].key = auxiliar1;
        arreglo[i].value = auxiliar2;
    }
    
    buildHeap(&H,arreglo,10);

    for(int i = 0 ; i < 10; i++ ){
        printf(" %d : [%d %d] ",i+1,arreglo[i].key,arreglo[i].value);
    }
    fclose(fo);
    printf("\n");
    /*for(int i = 0; i < HT2.maxSize;i++){
        printf("%d\n",HT2.table[i].codigo_producto);
        printf("------------------ \n");
    }*/
    //Para el resto es una cola


    clearHashp(&HT);
    clearHasho(&HT2);
    fclose(fc);
    return 0;
}
