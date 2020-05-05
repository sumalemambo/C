#include <stdio.h>
int main(){
    int i,contador;
    scanf("%d",&i);
    int array[i],d[i];
    for(int j=0; j<i ;j++){
        scanf("%d",&array[j]);
    }
    for(int j=0; j < i; j++){
        contador=1;
        for(int l=j+1; l < i;l++){
            if(array[j]==array[l]){
                array[l]=-1;
                contador+=1;
            }
        }
        if(array[j]!=-1){
            d[j]=contador;
        }
    }
    for(int j=0; j < i; j++){
        if(array[j]!=-1){
            printf("%d aparece %d vez(es)\n",array[j],d[j]);
        }
    }
    return 0;
}//falta agregar el sort!