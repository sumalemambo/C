#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){

    int contador;
    FILE *fp;
    char **p,c[201];
    p=(char**)malloc(sizeof(char*)*10000000);
    fp=fopen("S.txt","r");

    if(fp==NULL){
        printf("Error al abrir el archivo\n");
        exit(1);
    }
    
    while(fgets(c,201,fp)!=NULL){
        p[contador]=(char*)malloc(sizeof(char)*201);
        strcpy(p[contador],c);// c[0]
        printf("%s",p[contador]);
        contador+=1;
    }
    for(int i;  i < contador ;i++)
        free((void*)p[i]);
    fclose(fp);
    free((void*)p);
    return 0;
}
