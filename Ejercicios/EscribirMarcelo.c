#include <stdio.h>
int main(){
    int a[5]={4,1,3,3,2};

    FILE *fp=fopen("marcelo.txt","w");

    fwrite(a,sizeof(int),5,fp);
    
    fclose(fp);
    return 0;
}