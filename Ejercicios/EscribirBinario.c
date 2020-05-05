#include <stdio.h>
int main(){
    int a[15]={12,77,124,675,12321,4546,13,12,311,321,653,12,58,12,67};

    FILE *fp=fopen("maximoinfile.dat","w");

    fwrite(a,sizeof(int),15,fp);

    fclose(fp);
    return 0;
}