#define empty -1
#define MAX_SIZE 1000000
#define tableSize 13
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

typedef struct{
    producto* table;
    int prime;
    int maxSize;
    int size;
}hashP;

typedef struct{
    oferta* table;
    int prime;
    int maxSize;
    int size;
}hashO;

typedef struct{
    int key;
    int value;
}elem;

typedef struct{
    elem* array;
    int lenght;
}heap;
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
void initHash(hashP* HT){
    HT->maxSize = tableSize;
    HT->size = 0;
    HT->prime = 11;
    HT->table = (producto*)malloc(sizeof(producto)*tableSize);
    for(int i = tableSize;i--;){
        HT->table[i].codigo_producto = empty;
    }
}

int hashInsert(hashP* HT,producto data){

    int pos,h1_t,h2_t;
    pos = h1_t = h1(data.codigo_producto,HT->maxSize);
    h2_t = h2(data.codigo_producto,HT->prime);
    for(int i = 1; HT->table[pos].codigo_producto != empty && HT->table[pos].codigo_producto != data.codigo_producto;i++){
        pos = (h1_t + i * h2_t) % HT->maxSize;
    }
    if(HT->table[pos].codigo_producto == data.codigo_producto){
        return 0;
    }
    HT->table[pos] = data;
    HT->size++;
    return 1;
}

void rehash(hashP* HT){

    int lenght = HT->maxSize;
    HT->maxSize = findPrime(HT->maxSize*2);
    HT->prime = findPrime(HT->maxSize);
    producto* aux2 = HT->table;
    HT->table = (producto*)malloc(sizeof(producto)*HT->maxSize);
    HT->size = 0;
    for(int i = HT->maxSize;i--;){
        HT->table[i].codigo_producto = empty;
    }

    for(int i = lenght;i--;){
        if(aux2[i].codigo_producto != empty){
            hashInsert(HT,aux2[i]);
        }
    }

    free((void*)aux2);

}

producto* hashSearch(hashP* HT,int key){

    int pos,h1_t,h2_t;
    pos = h1_t = h1(key,HT->maxSize);
    h2_t = h2(key,HT->prime);
    for(int i = 1; HT->table[pos].codigo_producto != empty && HT->table[pos].codigo_producto != key;i++){
        pos = (h1_t + i * h2_t) % HT->maxSize;
    }
    if(HT->table[pos].codigo_producto == key){
        return &(HT->table[pos]);
    }
    return NULL;
}

void clearHashp(hashP* HT){
    free((void*)HT->table);
}

//Hash struct oferta
void initHashO(hashO* HT){

    HT->maxSize = tableSize;
    HT->size = 0;
    HT->prime = 11;
    HT->table = (oferta*)malloc(sizeof(oferta)*tableSize);
    for(int i = tableSize;i--;){
        HT->table[i].codigo_producto = empty;
    }
}

int hashInsertO(hashO* HT,oferta data){

    int pos,h1_t,h2_t;
    pos = h1_t = h1(data.codigo_producto,HT->maxSize);
    h2_t = h2(data.cantidad_descuento,HT->prime);
    for(int i = 1; HT->table[pos].codigo_producto != empty && HT->table[pos].codigo_producto != data.codigo_producto;i++){
        pos = (h1_t + i * h2_t) % HT->maxSize;
    }
    if(HT->table[pos].codigo_producto == data.cantidad_descuento){
        return 0;
    }
    HT->table[pos] = data;
    HT->size++;
    return 1;
}

oferta* hashSearchO(hashO* HT,int key){

    int pos, h1_t, h2_t;
    pos = h1_t = h1(key,HT->maxSize);
    h2_t = h2(key,HT->prime);
    for(int i = 1; HT->table[pos].codigo_producto != empty && HT->table[pos].codigo_producto != key;i++){
        pos = (h1_t + i * h2_t) % HT->maxSize;
    }
    if(HT->table[pos].cantidad_descuento == key){
        return &(HT->table[pos]);
    }
    return NULL;
}

void rehash2(hashO* HT){

    int lenght = HT->maxSize;
    HT->maxSize = findPrime(HT->maxSize * 2);
    HT->prime = findPrime(HT->maxSize);
    oferta* aux = HT->table;
    HT->table = (oferta*)malloc(sizeof(oferta)*HT->maxSize);
    HT->size = 0;

    for(int i = lenght;i--;){
        if(aux[i].codigo_producto != empty){
            hashInsertO(HT,aux[i]);
        }
    }
    free((void*)aux);
}

void clearHasho(hashO* HT){
    free((void*)HT->table);
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

//Heap
void maxHeapify(heap* H,int pos){
    
    int left = 2 * pos;
    int right = 2 * pos + 1;
    int aux = pos;
    if(left < H->lenght && H->array[pos].value < H->array[left].value){
        aux = left;
    }
    if(right < H->lenght && H->array[aux].value < H->array[right].value){
        aux = right;
    }
    if( aux != pos){
        elem aux2 = H->array[pos];
        H->array[pos] = H->array[aux];
        H->array[aux] = aux2;
        maxHeapify(H,aux);
    }
}

void buildHeap(heap* H,elem* array,int lenght){
    H->array = array;
    H->lenght = lenght;
    for(int i = lenght/2;i--;){
        maxHeapify(H,i);
    }
}

