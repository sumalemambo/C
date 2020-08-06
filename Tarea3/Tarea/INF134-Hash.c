#define empty -1
#define MAX_SIZE 1000000
#define tableSize 13

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
    int rep;
    int value;
    int accumulated;
}dato;

typedef struct node{
    dato info;
    struct node* left;
    struct node* right;
}binNode;

typedef struct{
    binNode* root;
}binTree;

typedef struct{
    dato* array;
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
    if(HT->table[pos].codigo_producto == key){
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
    for(int i = HT->maxSize;i--;){
        HT->table[i].codigo_producto = empty;
    }

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

//Heap
void Heapify(heap* H,int pos){
    
    int aux = pos;
    int left = 2 * pos;
    int right = 2 * pos + 1;
    dato auxiliar;
    if(left <= H->lenght &&  H->array[pos].value < H->array[left].value){
        aux = left;
    }
    if(right <= H->lenght && H->array[aux].value < H->array[right].value){
        aux = right;
    }
    if(aux != pos){
        auxiliar = H->array[pos];
        H->array[pos] = H->array[aux];
        H->array[aux] = auxiliar;
        Heapify(H,aux);
    }
}

void maxHeapify(heap* H){
    for(int i = H->lenght/2 ; i >=1 ; i--){
        Heapify(H,i);
    }
}

dato deleteMax(heap* H){
    dato aux = H->array[1];
    H->array[1] = H->array[H->lenght];
    H->lenght--;
    Heapify(H,1);
    return aux;
}


void buildHeap(heap* H,dato* array,int lenght){
    H->array = array;
    H->lenght = lenght;
}

void deleteHeap(heap* H){
    free((void*)H->array);
}

//arbol
void initTree(binTree* T){
    T->root = NULL;
}

void clearHelp(binNode* nodo){
    if( nodo == NULL){
        return;
    }
    clearHelp(nodo->left);
    clearHelp(nodo->right);
    free((void*)nodo);
}

void clearTree(binTree* T){
    clearHelp(T->root);
    T->root=NULL;
}

binNode* insertHelp(binNode* nodo,int key,int* size){
    if(nodo == NULL){
        nodo=(binNode*)malloc(sizeof(binNode));
        nodo->info.accumulated = 1;
        nodo->info.rep = 1;
        nodo->info.key = key;
        nodo->info.value = 0;
        nodo->left=NULL;
        nodo->right=NULL;
        (*size)++;
    }
    else if(nodo->info.key > key){
        nodo->left=insertHelp(nodo->left,key,size);
    }
    else if(nodo->info.key == key){
        nodo->info.rep ++;
        nodo->info.accumulated++;
    }
    else{
        nodo->right=insertHelp(nodo->right,key,size);
    }
    return nodo;
}

void insert(binTree* T,int key,int* size){
    T->root=insertHelp(T->root,key,size);
}

void PreOrderHelp2(binNode* nodo){
    if(nodo == NULL){
        return;
    }
    printf("--(%d , %d ,%d )--\n",nodo->info.key,nodo->info.rep,nodo->info.value);
    PreOrderHelp2(nodo->left);
    PreOrderHelp2(nodo->right);
}

void PreOrder2(binTree* T){
    PreOrderHelp2(T->root);
}

void treeAcHelp(binNode* nodo,hashP* HT,hashO* HT2){
    oferta* aux;
    if(nodo == NULL){
        return;
    }

    if( nodo->info.accumulated != 0){

        aux = hashSearchO(HT2,nodo->info.key);
        nodo->info.value += (hashSearch(HT,nodo->info.key)->precio * nodo->info.accumulated - ((aux == NULL)? 0 : (nodo->info.accumulated / aux->cantidad_descuento) * aux->monto_descuento));
        nodo->info.accumulated = 0;

    }

    treeAcHelp(nodo->left,HT,HT2);
    treeAcHelp(nodo->right,HT,HT2);
}

void treeAc(binTree* T,hashP* HT,hashO* HT2){
    treeAcHelp(T->root,HT,HT2);
}


void treeToArrayHelp(dato* array,binNode* T,int* i){
    if(T != NULL){
        array[(*i)++] = T->info;
        treeToArrayHelp(array,T->left,i);
        treeToArrayHelp(array,T->right,i);
    }
}

void treeToArray(dato* array,binTree* T){
    int i = 1;
    treeToArrayHelp(array,T->root,&i);
}