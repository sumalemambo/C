#include <stdio.h>

typedef struct{
    int codigo_producto;
    int cantidad_descuento;
    int monto_descuento;
}oferta;

int main(){
    FILE* fp = fopen("ofertas.dat","w");
    oferta help;
    int a = 1;
    help.codigo_producto = 1991;
    help.cantidad_descuento = 2;
    help.monto_descuento = 5;
    fwrite(&a,sizeof(int),1,fp);
    fwrite(&help,sizeof(oferta),1,fp);
    fclose(fp);
    return 0;
}
