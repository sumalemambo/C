#include <stdio.h>
#include <stdlib.h>

typedef struct Persona Persona;
struct Persona{
    char *nombre;
    int edad;
    int salario;
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
    Persona empleados[] = { {"Juan", 25, 5000},
                            {"Ana", 30, 6000},
                            {"Luis", 40, 7000},
                            {"Franciso", 50, 8000}};
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
    printf("Nombre: %s\n", persona->nombre);
    printf("Edad: %d\n", persona->edad);
    printf("Salario: %d\n", persona->salario);
}