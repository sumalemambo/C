#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **buscar_str(char **S, int n, char *P, int *largo){
    *largo=0;
    char **arreglo=(char**)malloc(sizeof(char*)*n);
    for(int i = 0; i < n; i++){
        if(strstr(S[i],P)){
            arreglo[*largo]=(char*)malloc(sizeof(char)*(strlen(S[i])+5));
            strcpy(arreglo[*largo],S[i]);
            (*largo)++;
        }
    }
    arreglo = (char**)realloc(arreglo,(*largo)*sizeof(char*));
    return arreglo;

}

int main(){

    FILE *fp = fopen("S.txt","r"),*escribo;
    int i = 0,largo=0; // no olvidar iniciarlo
    if(fp == NULL){
        printf("Error al abrir el archivo S\n");
        exit(1);
    }
    char **arreglo = (char**)malloc(sizeof(char*)*1000000),**arregloEscribir;
    char *cadena = (char *)malloc(sizeof(char)*201);
    while(fscanf(fp,"%s",cadena)==1){
        arreglo[i] = (char*)malloc(sizeof(char)*(strlen(cadena)+1));
        strcpy(arreglo[i],cadena);
        i++;
    }
    arreglo = (char**)realloc(arreglo,sizeof(char*)*i);
    fclose(fp);

    fp=fopen("P.txt","r");
    if(fp == NULL){
        printf("Error al abrir el archivo P\n");
        exit(1);
    }
    while(fscanf(fp,"%s",cadena)==1){
        arregloEscribir=buscar_str(arreglo,i,cadena,&largo);
        escribo=fopen(strcat(cadena,".out"),"w");
        for(int j=0; j < largo-1 ; j++){
            fprintf(escribo,"%s\n",arregloEscribir[j]);
            free((void*)arregloEscribir[j]);
        }
        if(largo!=0){
            fprintf(escribo,"%s\n",arregloEscribir[largo-1]);
            free((void*)arregloEscribir[largo-1]);
        }
        free((void*)arregloEscribir);
        fclose(escribo);
    }
    fclose(fp);
    for (int j = 0; j < i; j++){
        free((void*)arreglo[j]);
    }
    free((void*)arreglo);
    free((void*)cadena);
    return 0;
}
