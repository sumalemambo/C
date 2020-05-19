#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char **buscar_str(char **S, int n, char *P, int *largo){

    int contador;
    char **arreglo=(char**)malloc(sizeof(char*)*n);
    printf("%s",S[1]);
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

    FILE *fp = fopen("S.txt","r"),*escribo;
    int i = 0,largo; // no olvidar iniciarlo
    if(fp == NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    char **arreglo = (char**)malloc(sizeof(char*)*1000000),**arregloEscribir;
    char *cadena = (char *)malloc(sizeof(char)*201);
    while(fgets(cadena, 201, fp) != NULL){
        arreglo[i] = (char*)malloc(sizeof(char)*(strlen(cadena)+1));
        strcpy(arreglo[i],cadena);
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
        arregloEscribir=buscar_str(arreglo,i,cadena,&largo);
        escribo=fopen("SD.txt","w");
    }
    fclose(escribo);
    for (int b = 0; b < i; b++)
    {
        free((void*)arreglo[b]);
    }
    free((void*)arreglo);
    free((void*)cadena);
    return 0;
}
