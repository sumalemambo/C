#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* char **buscar_str(char **S, int n, char  *P,int *largo){
    int contador;
    char **arreglo=(char**)malloc(sizeof(char*)*1000000),**arreglofinal;
    for(int i,j; i < n; i++){
        if(strstr(S[i],P)){
            arreglo[j]=(char*)malloc(sizeof(char)*(strlen(S[i])+1));
            strcpy(arreglo[j],S[i]);
            contador+=1;
            j++;
        }
    }
    for(int i;i < contador+1;i++){
        free((void*)arreglo[i]);
    }
    free((void*)arreglo);
}*/
int main(){
    int contador,*largo;
    char **strings=(char**)malloc(sizeof(char*)*1000000),*aux=(char*)malloc(sizeof(char)*201),*prefijo=(char*)malloc(sizeof(char)*201);
    FILE *fp=fopen("S.txt","r");

    while(fgets(aux,201,fp)!=NULL){
        strings[contador]=(char*)malloc(sizeof(char)*(strlen(aux)+1));
        strcpy(strings[contador],aux);
        contador+=1;
    }
    fclose(fp);
    fp=fopen("P.txt","r");
    while(fgets(aux,201,fp)!=NULL){
        buscar_str(strings,contador+1,aux,largo);
    }
    free((void*)aux);
    for(int i; i < contador+1; i++){
        free((void*)strings[i]);
    }
    free((void*)prefijo);
    free((void*)strings);
    return 0;
}
