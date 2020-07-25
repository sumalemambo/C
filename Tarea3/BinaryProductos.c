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
    int a = 13;
    fwrite(&a,sizeof(int),1,fp);

    write.codigo_producto = 21;
    strcpy(write.nombre_producto,"Miel");
    write.precio = 2400;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 1;
    strcpy(write.nombre_producto,"Carne vacuno");
    write.precio = 1500;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 13;
    strcpy(write.nombre_producto,"Atun");
    write.precio = 600;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 127;
    strcpy(write.nombre_producto,"Nutella");
    write.precio = 3700;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 61;
    strcpy(write.nombre_producto,"Carbon");
    write.precio = 800;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 53;
    strcpy(write.nombre_producto,"Arroz");
    write.precio = 300;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 321;
    strcpy(write.nombre_producto,"Cafe");
    write.precio = 1100;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 101;
    strcpy(write.nombre_producto,"Te");
    write.precio = 800;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 37;
    strcpy(write.nombre_producto,"Mermelada");
    write.precio = 300;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 93;
    strcpy(write.nombre_producto,"Yoghurt");
    write.precio = 150;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 42;
    strcpy(write.nombre_producto,"Pollo");
    write.precio = 1300;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 78;
    strcpy(write.nombre_producto,"Papas fritas");
    write.precio = 780;
    fwrite(&write,sizeof(producto),1,fp);

    write.codigo_producto = 24;
    strcpy(write.nombre_producto,"Leche");
    write.precio = 450;
    fwrite(&write,sizeof(producto),1,fp);
    

    fclose(fp);
    return 0;
}