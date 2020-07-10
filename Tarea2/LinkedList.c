typedef struct Node{
    struct Node* next;
    struct Node* prev;
    int initByte;
    int endByte;
}node;

typedef struct{
    node* head;
    node* curr;
    node* tail;
    int size;
    int byte;
}list;

int frontValue(list* L){
    return L->curr->next->initByte;
}

int byte(list* L){
    return L->byte;
}

int lenght(list* L){
    return L->size;
}

void next(list* L){
    if(L->curr == L->tail){
        return;
    }
    L->curr = L->curr->next;
}

void moveToStart(list* L){
    L->head=L->curr;
}

int getValue(list* L){
    return (L->curr->next->endByte - L->curr->next->initByte+1);
}

void initList(list* L){
    L->tail=L->curr=L->head=(node*)malloc(sizeof(node));
    L->size=L->byte=0;
}

void insert(list* L,int byte1,int byte2){
    node* aux = L->curr->next;
    L->curr->next=(node*)malloc(sizeof(node));
    L->curr->next->initByte=byte1;
    L->curr->next->endByte=byte2;
    L->curr->next->next=aux;
    if(L->curr == L->tail){
        L->tail = L->curr->next;
    }
    else{
        L->curr->next->next->prev=L->curr->next;
    }
    L->size++;
    L->byte+=getValue(L);
}

void clear(list* L){
    if(L->head == L->tail){
        return;
    }
    node* aux;
    moveToStart(L);
    L->byte-=getValue(L);
    while(L->curr->next != L->tail){
        aux=L->curr->next->next;
        free((void*)L->curr->next);
        L->curr->next=aux;
    }
    free((void*)L->tail);
    L->curr=L->tail=L->head;
    L->size=L->byte=0;
}

void deleteList(list* L){
    clear(L);
    free((void*)L->head);
}

void erase(list* L){
    if(L->curr == L->tail){
        return;
    }
    node* aux = L->curr->next->next;
    L->byte-=getValue(L);
    if(L->curr->next == L->tail){
        L->tail = L->curr;
        free((void*)L->curr->next); 
    }
    else{
        L->curr->next->prev = L->curr;
    }
    L->curr->next=aux;
    L->size--;
}

void swap(list* L1,list* L2,int val){
    insert(L2,frontValue(L1),frontValue(L1)+val-1);
    L1->byte-=val;
    L1->curr->next->initByte+=val;
    if(L1->curr->next->endByte+1 == L1->curr->next->initByte){
        erase(L1);
    }
}
