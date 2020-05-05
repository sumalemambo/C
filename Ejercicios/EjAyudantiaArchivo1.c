#include <stdio.h>
int main(){

    int n;
    float prom;
    FILE *fp= fopen("marcelo.txt","r");
    fread(&n,sizeof(int),1,fp);
    int a[n];
    fread(a,sizeof(int),n,fp);

    for(int i =0 ; i < n ; i++){
        if(a[i]==0){
            prom+=a[i];
            printf("%d\n",a[i]);
        }
        else{
            prom+=(a[i]/2);
            printf("%f\n",prom);
        }

    }
    fclose(fp);
    return 0;
}