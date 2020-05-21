#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(){
    FILE *fp=fopen("transacciones.txt","r");
    int Transacciones=0;
    char b;
    int nLineas=0;
    while((b=fgetc(fp))!=EOF) {
        if(b=='+' || b=='-')
            Transacciones++;
        else if(b=='>'){
            Transacciones+=2;
        nLineas++;
        }
    }
    printf("%d",Transacciones);
    fclose(fp);
    return 0;
}
