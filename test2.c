#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    FILE *fp = fopen("S.txt","r");
    int i = 0;
    
    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    char **arreglo = (char**)malloc(sizeof(char*)*1000000);
    char *cadena = (char *)malloc(sizeof(char)*201);

    while(fgets(cadena, 201, fp) != NULL){
        arreglo[i] = (char*)malloc(sizeof(char)*(strlen(cadena)+1));
        strcpy(arreglo[i],cadena);
        i++;
    }
    arreglo = (char**)realloc(arreglo,sizeof(char*)*i);
    fclose(fp);
    for (int b = 0; b < i; b++)
    {
        free((void*)arreglo[b]);
    }
    free((void*)arreglo);
    free((void*)cadena);
    return 0;
}
