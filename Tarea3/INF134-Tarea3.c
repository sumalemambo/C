#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "INF134-Hash.c"

int main(){
    FILE* fp=fopen("productos.dat","r");
    FILE* fo=fopen("ofertas.dat","r");
    FILE* fc=fopen("compras.txt","r");
    if(fp == NULL || fo == NULL || fc == NULL){
        printf("ERROR: Hubo un problema al abrir los archivos.\n");
        exit(1);
    }

    int n,valp,valo,ranking,compras,key;
    producto* hashProd;
    producto help;
    oferta* hashOffer;
    oferta helpO;
    queue p;

    fread(&n,sizeof(int),1,fp);
    valp = n * 1.7;
    hashProd = (producto*)malloc(sizeof(producto)*valp);
    initHashP(hashProd,valp);

    while(n != 0){
        fread(&help,sizeof(producto),1,fp);
        hashInsertP(hashProd,help,valp);
        n--;
    }

    /*for(int i = 0; i < valp; i++ ){
        printf("%d %d %s\n",hashProd[i].codigo_producto,hashProd[i].precio,hashProd[i].nombre_producto);
        printf("--------------------\n");
    }*/

    fclose(fp);
    fread(&n,sizeof(int),1,fo);
    valo = n * 1.7;
    hashOffer = (oferta*)malloc(sizeof(oferta)*valo);
    initHashO(hashOffer,valo);
    initQueue(&p);

    while( n != 0 ){
        fread(&helpO,sizeof(oferta),1,fo);
        hashInsertO(hashOffer,helpO,valo);
        n--;
    }
    fclose(fo);
    //Para el resto es una cola
    fscanf(fc,"%d ",&ranking);
    fscanf(fc,"%d ",&n);

    while( n != 0 ){
        fscanf(fc,"%d ",&compras);
        while( compras != 0){
            fscanf(fc,"%d ",&key);
            enqueue(&p,key); // trabajar con una pseudo-cola ,insertar comparar con el inicial si son distintos muevo la posicion inicial a size y inserto size elementos al arbol
            compras--;
        }
        
        clear(&p);
        n--;
    }


    deleteQueue(&p);
    free((void*)hashProd);
    free((void*)hashOffer);
    fclose(fc);
    return 0;
}
