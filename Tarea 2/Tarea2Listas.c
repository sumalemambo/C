#include <stdio.h>
#include <stdlib.h>

typedef int elementoLista; //Tipo de datos dentro de la lista

typedef struct 
{
    int MAX; //Maximo tamaño de la lista(El max que puede tener)
    int Side;   //Tamaño Actual de la lista
    int curr; //Posicion Actual de la lista
    elementoLista* listarray; //Array con los elementos de la lista
}Lista; //Struct Lista

//Functions Lista
void NextPos(Lista* l) {if(l->curr != l->Side) l->curr++;} //Siguiente posicion
void PrevPos(Lista* l) {if(l->curr != 0) l->curr--;} //Anterior posicion
void StartPos(Lista* l){l->curr = 0;} //Inicio de la lista
void EndPos(Lista* l){l->curr = l->Side;} //Fin de la lista
int SeeSide(Lista* l){return l->MAX;}

void CrearLista(Lista* l,int MaxSizes){
    l->MAX = MaxSizes;
    l->Side = 0;
    l->curr = 0;
    l->listarray = malloc(l->MAX*sizeof(elementoLista));
}

void Clear(Lista* l){
    free(l->listarray);
    l->Side = l->curr = 0;
    l->listarray = malloc(l->MAX*sizeof(elementoLista));
}

int push(Lista* l, elementoLista item){
    int i = 0;
    if(l->Side >= l->MAX){
        return -1; //Lista supera su maximo
    }
    for(i = l->Side; i > l->curr;i--){
        //printf("In space %d inserts element %d\n",i,item);
        l->listarray[i] = l->listarray[i-1];
    }
    l->listarray[i] = item;
    l->Side++;
    return i; //retorna la posicion de inscercion
}

int append(Lista* l, elementoLista item){
    if(l->Side >= l->MAX){
        return 0; //Lista supera su maximo
    }
    l->listarray[l->Side++] = item;
    return 1;
}

int SearchElement(Lista* l,elementoLista item){
    int i = 0;
    l->curr = 0;
    for (i = l->curr; i < l->Side; i++){ //Recorre la lista
        if (l->listarray[i] == item){
            return i; //Encontro el elemento en la posicion i
        }
    }
    return 0; //No existe el elemento
}

int SeePos(Lista* l,int pos){
    if(pos >= l->Side){
        return 0; //Espacio fuera de los elementos de la lista
    }
    return (l->listarray[pos]); //Retorna elemento en posicion pos
}

void AumentarTamano(Lista* l,int MaxDeseado){
    l->MAX = MaxDeseado; //Maximo deseado por el usuario
    realloc(l->listarray,MaxDeseado*sizeof(elementoLista));
}

int pop(Lista* l){
   if ((l->curr >= 0) && (l->curr < l->Side)){
       int poped = l->listarray[l->curr];
       for (int i = l->curr; i < l->Side-1; i++){
           l->listarray[i] = l->listarray[i+1];
       }
       l->Side--;
       return poped;
   }
}

void SeeAll(Lista* l){
    printf("[");
    for (int i = 0; i < l->Side; i++) //recorre todas las posiciones de la lista
    {
        printf("%d,",SeePos(l,i)); //Ve la posicon i
    }
    printf("]\n");
}

typedef struct 
{
    Lista* Head; //List After Current
    Lista* Tail; //List before current
    Lista* Curr; //Current List
}Enlaze; //Struct Enlaze entre listas

//Function Enlaze
void CreateEnlazeBegin(Enlaze* E,Lista* l){
    E->Head =E->Tail =E->Curr = l;
}

void CreateEnlazeHead(Enlaze* E,Lista* l){
    E->Head = l;
}

void CreateEnlazeTail(Enlaze* E,Lista* l){
    E->Tail = l;
}

void FreeBlock(Lista* l){
    free((void*)l);
}