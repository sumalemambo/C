#include <stdio.h>
float minimo(float x,float *y){
    
    int contador;

    for(int i = 0 ; i < 6 ; i++){
        while(x <= y[i]){
            x=-y[i];
            contador++;
        }
    }
    return x;
}
int main(){
    float valor, moenas[6] = {1,0.5,0.25,0.10,0.05,0.01}, notas[6] = {100,50,20,10,5,2},a;
    scanf("%f",&valor);
    valor=minimo(valor,moenas);
    printf("%f",a);
    return 0;
}