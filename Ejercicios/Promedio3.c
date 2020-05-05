#include <stdio.h>
#include <math.h>
int main(){
    float a,b,c,d,e,promedio;
    scanf("%f %f %f %f", &a, &b, &c, &d);
    promedio=(a+b+c+d)/4;
    promedio=round(promedio*10)/10;
    if(promedio>=7)
        printf("Media: %.1f\nAluno aprovado.\n",promedio);
    if(promedio>=5 && promedio<=6.9){
        scanf("%f",&e);
        printf("Media: %.1f\nAluno em exame.\n",promedio);
        promedio=(promedio+e)/2;
        promedio=round(promedio*10)/10;
        printf("Nota do exame: %.1f\n",e);
        if(promedio>=5)
            printf("Aluno aprovado.\nMedia final: %.1f\n",promedio);
        else{
            printf("Aluno reprovado.\nMedia final: %.1f\n",promedio);
        }
    }
    else{
        printf("Media: %.1f\nAluno reprovado.\n");
    }
    return 0;
}