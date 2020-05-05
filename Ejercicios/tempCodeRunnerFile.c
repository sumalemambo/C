#include <stdio.h>
int main(){
    float x,y;
    scanf("%f %f",&x,&y);
    if(x&&y!=0){
        if(x>0 && y>0){
            printf("Q1\n");
        }
        if(x<0 && y>0){
            printf("Q2\n");
        } 
        if(x<0 && y<0){
            printf("Q3\n");
        }
        if(x>0 && y<0){
            printf("Q4\n");
        }
    }
    else{
        printf("Origem\n");
    }
    return 0;
}