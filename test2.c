#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **buscar_str(char **S, int n, char *P, int *largo){
    int contador;
    printf("%d\n",n);
    printf("%s\n",S[1]);
    *largo=2;
    printf("%d\n",*largo);
    printf("%s",P);
}

int main(){

    FILE *fp = fopen("S.txt","r");
    int i = 0,*largo; // no olvidar iniciarlo
    *largo=0;
    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    char **arreglo = (char**)malloc(sizeof(char*)*1000000),**arregloEscribir;
    char *cadena = (char *)malloc(sizeof(char)*201);
    while(fgets(cadena, 201, fp) != NULL){
        arreglo[i] = (char*)malloc(sizeof(char)*(strlen(cadena)+1));
        strcpy(arreglo[i],cadena);
        printf("%s\n",arreglo[i]);
        i++;
    }

    arreglo = (char**)realloc(arreglo,sizeof(char*)*i);
    fclose(fp);

    fp=fopen("P.txt","r");
    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    while(fgets(cadena,201,fp)){
        arregloEscribir=buscar_str(arreglo,i,cadena,largo);
    }
    for (int b = 0; b < i; b++)
    {
        free((void*)arreglo[b]);
    }
    free((void*)arreglo);
    free((void*)cadena);
    return 0;
}
