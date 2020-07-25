#include <stdio.h>

typedef struct{
    int codigo_producto;
    char nombre_producto[31];
    int precio;
}producto;

int main(){
    FILE* fp = fopen("productos.dat","r");
    producto aux;
    int entero;
    fread(&entero,sizeof(int),1,fp);
    while(fread(&aux,sizeof(producto),1,fp) > 0){
        printf("%d\n",aux.codigo_producto);
        printf("%s\n",aux.nombre_producto);
        printf("%d\n",aux.precio);
        printf("------------------------\n");
    }

    fclose(fp);
    return 0;
}