#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){

    char **strings,temporal[200];
    strings=(char**)malloc(200*1000000*sizeof(char));
    FILE *fp=fopen("S.txt","r");
    int contador=0;

    while(fgets(temporal,200,fp)>0){
        strcpy(strings[contador],temporal);
        contador+=1;
    }
    fclose(fp);
    free((void *)strings);
    return 0;
}