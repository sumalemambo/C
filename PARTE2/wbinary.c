#include <stdio.h>
#include <stdlib.h>

typedef struct Persona Persona;

struct Persona{
    int nroCuenta;
    int saldo;
    char nbre[51];
    char direccion[51];
};

int escribeArchivo(Persona empleados[], int tam, char *nombreArchivo);
int leeArchivo(Persona empleados[], int tam, char *nombreArchivo);
void imprimeEmpleados(Persona empleados[], int tam);
void imprimePersona(Persona *persona);

int escribeArchivo(Persona empleados[], int tam, char *nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo, "w");
    if(fp == NULL){
        puts("NO SE PUDO ABRIR EL ARCHIVO");
        return 0;
    }
    for (int i = 0; i < tam; i++)
    {
        fwrite(&empleados[i], sizeof(Persona), 1 ,fp);
    }
    fclose(fp);
    return 1;
}
int leeArchivo(Persona empleados[], int tam, char *nombreArchivo)
{
    FILE *fp = fopen(nombreArchivo, "r");
    if(fp == NULL){
        puts("NO SE PUDO ABRIR EL ARCHIVO");
        return 0;
    }
    for (int i = 0; i < tam; i++)
    {
        fread(&empleados[i], sizeof(Persona), 1 ,fp);
    }
    fclose(fp);
    return 1;
}

int main()
{
Persona empleados[] = { { 1, 10000, "Nacho", "LasCondes"},
                        { 2, 5000, "Seba", "Nunoa"},
                        { 3, 7000, "David", "Buin"},
                        { 4, 500, "Junanin", "Nose"}};
    int tam = sizeof(empleados)/sizeof(Persona);
    Persona empleadosEntrada[tam];
    if(!escribeArchivo(empleados, tam, "clientes.txt")){
        printf("ERROR DE ESCRITURA\n");
        return 1;
    }
    if(!leeArchivo(empleadosEntrada, tam, "clientes.txt")){
        printf("ERROR DE LECTURA\n");
        return 2;
    }
    imprimeEmpleados(empleadosEntrada, tam);
    return 0;
}

void imprimeEmpleados(Persona empleados[], int tam){
    for (int i = 0; i < tam; i++)
    {
        imprimePersona(&empleados[i]);
        printf("\n");
    }
}
void imprimePersona(Persona *persona){
    printf("Numero de cuenta: %d\n", persona->nroCuenta);
    printf("Saldo: %d\n", persona->saldo);
    printf("Nombre: %s\n", persona->nbre);
    printf("Direccion: %s\n", persona->direccion);
}