#include <stdio.h>
void sumar(int *p){
    (*p)++;
}
int main(){
    int d;
    scanf("%d",&d);
    sumar(&d);
    printf("El valor retornardo es %d",d);
    return 0;
}