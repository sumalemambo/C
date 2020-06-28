//Pregunta 1
/*
Se desea implementar un administrador de memoria dinamica, en donde se tiene una MDI(Memoria Dinamica) de M bytes
continuos (No es Lista enlazadas) inicialmente.
Mediantes ciertos procesos bloques de memoria aumentan m bytes o se liberan.
Es por ello que el se debe administrar un modo de listas enlazadas, donde se tienen dos tipos:

-Lista de bloques disponibles (L 1 ): cada nodo de la lista almacenará un bloque de memoria disponible,
representado por dos números enteros. Estos indican el byte de comienzo y el byte de final ocupados por 
el bloque. Inicialmente esta lista contiene un único nodo, que representa el bloque de memoria
[1..M ]. Los nodos de la lista se mantienen ordenados por el byte de comienzo de los bloques libres.

-Lista de bloques asignados (L 2 ): esta lista se mantiene de manera similar a la anterior, salvo que 
no es necesario mantener el orden de los nodos. Inicialmente, la lista está vacía (no hay bloques asignados).

//Dos listas ordenadas, una ordenada y otra no. Cada lista posee dos datos.
*/

#include "Tarea2Listas.c"
#include <string.h>

void Main(){
    int M,N,Cant; //M = Cantidad total de bytes, N = Cantidad total de operaciones, Cant= Cantidad del proceso
    char Op;
    FILE* fp;
    fp = fopen("input1.dat","r");
    fscanf(fp,"%d\n%d",&M,&N);
    for (int i = 0; i < N; i++)
    {
        fscanf(fp,"%s %d",&Op,&Cant); //Op has Malloc/Free Cantidad bytes
        if(Op == "malloc"){
            printf("Operacion Aumenta Memoria\n");
            break;
        }
        else if(Op == "free")
        {
            printf("Operacion Disminuye Memoria\n");
            break;
        }
        else{
            printf("Operacion No Valida\n");
            break;
        }
    }
    fclose(fp);
}
