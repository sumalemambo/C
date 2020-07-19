#define empty -1
#define MAX_SIZE 1000000
#include <stdlib.h>

typedef struct{
    int codigo_producto;
    char nombre_producto[31];
    int precio;
}producto;

typedef struct{
    int codigo_producto;
    int cantidad_descuento;
    int monto_descuento;
}oferta;

typedef struct Node{
    struct Node* left;
    struct Node* right;
    int key;
    int value;
}node;

typedef struct{
    node* root;
}tree;

typedef struct{
    int* tqueue;
    int size;
    int pos;
}queue;
//Test de primalidad: solo verifico hasta el n/2 ya que cualquier numero mayor no podra dividir de manera entera a mi numero
// estoy chequeando hasta el data/2 ya que necesito encontrar el menor estricto a M.
//Hay un problema si el largo del struct producto es 1, en ese caso el minimo primo es 1, hay que ver eso.

int prime(int data){
    int i;
    for(i = 2; i < data/2 ; i++){
        if( data % i == 0 ){
            i = 0;
            break;
        }
    }
    return (i == 0)? 0 : 1;
}

int findPrime(int data){
    int i,max = 0;
    for(i = 1; i < data ;i++){
        if(prime(i) == 1){
            max = i;
        }
    }
    return max;
}

//Funciones h1,h2
int h1(int key,int lenght){
    return key % lenght;
}

int h2(int key,int lenght){
    return lenght - (key % lenght);
}

// Hash struct producto
void initHashP(producto* HT,int lenght){
    for(int i = lenght; i--;){
        HT[i].codigo_producto = empty;
    }
}

int hashInsertP(producto* HT,producto data,int lenght){

    int start,i,pos,primo;
    primo = findPrime(lenght);
    pos = start = h1(data.codigo_producto,lenght);
    for(i = 1; HT[pos].codigo_producto != empty  && HT[pos].codigo_producto != data.codigo_producto; i++){
        pos = (start + i * h2(data.codigo_producto,primo)) % lenght;
    }
    if(HT[pos].codigo_producto == data.codigo_producto){
        return 0;
    }
    else{
        HT[pos] = data;
        return 1;
    }
}

producto* hashSearchP(producto* HT,int key,int lenght){

    int start,i,pos,primo;
    primo = findPrime(lenght);
    pos = start = h1(key,lenght);
    for(i = 1; HT[pos].codigo_producto != empty && HT[pos].codigo_producto != key; i++){
        pos = (start + i * h2(key,primo)) % lenght;
    }
    if(HT[pos].codigo_producto == key){
        return &(HT[pos]);
    }
    else{
        return NULL;
    }
}

//Hash struct oferta
void initHashO(oferta* HT,int lenght){
    for(int i = lenght;i--;){
        HT[i].codigo_producto = -1;
    }
}

int hashInsertO(oferta* HT,oferta data,int lenght){

    int start,i,pos,primo;
    primo = findPrime(lenght);
    pos = start = h1(data.codigo_producto,lenght);
    for(i = 1; HT[pos].codigo_producto != empty  && HT[pos].codigo_producto != data.codigo_producto; i++){
        pos = (start + i * h2(data.codigo_producto,primo)) % lenght;
    }
    if(HT[pos].codigo_producto == data.codigo_producto){
        return 0;
    }
    else{
        HT[pos] = data;
        return 1;
    }
}

producto* hashSearchO(producto* HT,int key,int lenght){

    int start,i,pos,primo;
    primo = findPrime(lenght);
    pos = start = h1(key,lenght);
    for(i = 1; HT[pos].codigo_producto != empty && HT[pos].codigo_producto != key; i++){
        pos = (start + i * h2(key,primo)) % lenght;
    }
    if(HT[pos].codigo_producto == key){
        return &(HT[pos]);
    }
    else{
        return NULL;
    }
}

//queue
void initQueue(queue* p){
    p->tqueue = (int*)malloc(sizeof(int) * MAX_SIZE);
    p->size = p->pos = 0;
}

void enqueue(queue* p,int data){
    p->tqueue[p->size++] = data;
}

int dequeue(queue* p){
    if(p->size == 0){
        return empty;
    }
    p->size--;
    return p->tqueue[p->pos++];
}

int frontValue(queue* p){
    return p->tqueue[p->pos];
}

void clear(queue* p){
    p->size = p->pos = 0;
}

void deleteQueue(queue* p){
    free((void*)p->tqueue);
}

//arbol
