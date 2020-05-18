#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **buscar_str(char **S, int n, char *P, int *largo){
    int contador;
    char **arreglo=(char**)malloc(sizeof(char*)*(n+1)),**arreglofinal;
    for(int i = 0; i < n; i++){
        if(strstr(S[i],P)){
            arreglo[contador]=(char*)malloc(sizeof(char)*(strlen(S[contador])+1));
            strcpy(arreglo[contador],S[i]);
            contador++;
        }
    }
    arreglo = (char**)realloc(arreglo,(contador + 1)*sizeof(char*));
    *largo = contador + 1;
    return arreglo;
}
int main(){

    FILE *fp = fopen("S.txt","r");
    int i = 0;
    
    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }

    char **arreglo = (char**)malloc(sizeof(char*)*1000000);
    char *cadena = (char *)malloc(sizeof(char)*201);
    char **arreglop;
    int *largo;
    FILE *fpp;
    
    while(fgets(cadena, 201, fp) != NULL){
        printf("%s\n",cadena);
        arreglo[i] = (char*)malloc(sizeof(char)*201);
        arreglo[i]= (char*)realloc(arreglo[i],(strlen(cadena)+ 1)*sizeof(char));
        strcpy(arreglo[i],cadena);
        i++;
    }
    arreglo = (char**)realloc(arreglo,(i + 1)*sizeof(char*));
    fclose(fp);
    fp = fopen("P.txt","r");
    
    while(fgets(cadena, 201, fp)!= NULL){
        arreglop = buscar_str(arreglo, i + 1, cadena, largo);
        fpp = fopen(cadena,"w");
        for (int j = 0; j < largo; j++)
        {
            fprintf(fpp, "%s\n", arreglop[j]);
            free((void*)arreglop[j]);
        }
        free((void*)arreglop);
        fclose(fpp);
    }
    for (int b = 0; b < i; b++)
    {
        free((void*)arreglo[b]);
    }
    free((void*)arreglo);
    free((void*)cadena);
    return 0;
}
