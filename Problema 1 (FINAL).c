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

/*****
* TipoFunción: char NombreFunción: buscar_str
******
* Resumen Función
*Primero realizamos una variable la cual sera el largo de nuestro arreglo final que retornaremos con las 
*palabras, luego creamos un arreglo donde guardaremos esas palabras, y luego vamos viendo si el prefijo
*corresponde a la palabra, y si lo hace, se agrega al arreglo, y una vez iteradas todas las palabras, 
*se realiza un reajuste de la memoria, con las palabras que corresponde al prefijo otorgado, y se retorna
*el arreglo con las palabras de dicho prefijo.
******
* Input: char **S, int n, char *P, int *largo
* tipoParámetra NombreParámetro : Un arreglo con las palabras a analizar, el largo, el prefijo, y el largo del arreglo final.
******
* Returns:
* TipoRetorno: char , Descripción retorno: retorna un arreglo con las palabras que tienen ese prefijo.
*****/

int main(){
    FILE *fp = fopen("S.txt","r"),*escribo;
    int i = 0, largo; // no olvidar iniciarlo
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
        for(int j=0;j < largo-1 ; j++){
            fprintf(escribo,"%s\n",arregloEscribir[j]);
            free((void*)arregloEscribir[j]);
        }
        fprintf(escribo,"%s",arregloEscribir[largo-1]);
        free((void*)arregloEscribir[largo-1]);
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

/*****
* TipoFunción: int, NombreFunción: main
******
* Resumen Función
*Lo primero que se realizamos fue crear una memoria donde guardaremos todas nuestras palabras,
*las cuales pueden llegar a ser 1000000, y estas con un largo de 200 caracteres, y a continuación
*leemos el archivo para saber cuanto se ocupara de esa memoria, para luego reducirla si no se ocupa todo
*el espacio de la memoria que creamos, a continuación leemos el archivo P donde estan los prefijos que
*debemos saber si se encuentran en el otro archivo, entonces invocamos la otra función para realizar esa 
*operación y esta nos retornaria las palabras que tengan esos prefijos, para luego escribir un archivo de 
*texto para cada palabra que tenian esos prefijos, y luego vamos liberando la memoria que solicitamos.
******
* Input:
* tipoParámetra NombreParámetro : no recibe parametros, ya que es el que permite la ejecución del programa completo.
******
* Returns:
* TipoRetorno: retorna el entero 0, Descripción retorno: el fin de ejecución del programa 
*****/
