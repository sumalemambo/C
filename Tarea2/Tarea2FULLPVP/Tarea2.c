#include <stdio.h>
#include <stdlib.h>
#include "List.c"


int main(){
    FILE* fp=fopen("input1.dat","r");
    FILE* fw=fopen("output1.dat","w");
    if( fp == NULL || fw == NULL){
        printf("ERROR: No se pudo abrir el/los archivo/s\n");
        exit(1);
    }
    list memalloc,memfree;
    int M,N,val,i;
    char c,str[7];
    
    initList(&memalloc);
    initList(&memfree);
    fscanf(fp,"%d ",&M);
    fscanf(fp,"%d ",&N);
    insert(&memalloc,1,M);

    while( N != 0){
        fscanf(fp,"%c",&c);
        switch(c){
            case 'm':   fscanf(fp,"%6s",str);
                        fscanf(fp,"%d ",&val);
                        moveToStart(&memalloc);
                        for(i = lenght(&memalloc);i--;){
                            if(getValue(&memalloc) >= val){
                                fprintf(fw,"Bloque de %d bytes asignado a partir del byte %d\n",val,frontValue(&memalloc));
                                swap(&memalloc,&memfree,val);
                                i=1;
                                break;
                            }
                            next(&memalloc);
                        }
                        if(i == -1) fprintf(fw,"Bloque de %d bytes NO puede ser asignado\n",val);
                        break;

            case 'f':   fscanf(fp,"%4s",str);
                        fscanf(fp,"%d ",&val);
                        find(&memfree,val);
                        findAlloc(&memalloc,frontValue(&memfree));
                        insert(&memalloc,frontValue(&memfree),endValue(&memfree));
                        fprintf(fw,"Bloque de %d bytes liberado\n",getValue(&memfree));
                        check(&memalloc);
                        erase(&memfree);
                        break;

        }

        N--;
    }
    moveToStart(&memalloc);
    for(int i =lenght(&memalloc);i--;){
        printf("%d %d ->",frontValue(&memalloc),endValue(&memalloc));
        next(&memalloc);
    }

    i = lenght(&memfree);
    if(i == 0){
        fprintf(fw,"Toda la memoria dinamica pedida fue liberada");
    }
    else{
        fprintf(fw,"Quedaron %d bloques de memoria sin liberar (%d bytes)",i,bytes(&memfree));
    }

    deleteList(&memalloc);
    deleteList(&memfree);
    fclose(fp);
    fclose(fw);
    return 0;
}
