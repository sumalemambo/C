typedef struct{
    int codigo_producto;
    char nombre_producto[31];
    int precio;
}producto;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    FILE* fp=fopen("productos.dat","w");
    producto write;
    int a = 6;
    fwrite(&a,sizeof(int),1,fp);

    write.codigo_producto = 2020;
    strcpy(write.nombre_producto,"Papel Higienico");
    write.precio = 1034;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 430;
    strcpy(write.nombre_producto,"Aceite");
    write.precio = 879;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 1981;
    strcpy(write.nombre_producto,"Arroz");
    write.precio = 570;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 1346;
    strcpy(write.nombre_producto,"Lata de Atun");
    write.precio = 1450;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 1918;
    strcpy(write.nombre_producto,"Azucar");
    write.precio = 770;
    fwrite(&write,sizeof(producto),1,fp);
    
    write.codigo_producto = 1991;
    strcpy(write.nombre_producto,"Porotos");
    write.precio = 250;
    fwrite(&write,sizeof(producto),1,fp);
    
    fclose(fp);
    return 0;
}
