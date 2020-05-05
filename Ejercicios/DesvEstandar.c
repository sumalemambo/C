#include <stdio.h>
#include <math.h>
int main(){
    float prom,promf;
    int n;
    scanf("%d",&n);
    float a[n];
    for(int j=0; j < n ; j++){
        scanf("%f",&a[j]);
        prom+=a[j];
    }
    prom=prom/n;
    for(int j=0; j < n ; j++){
        promf+=(pow(a[j]-prom,2)/n);
    }
    printf("%f",promf);
    return 0;
}