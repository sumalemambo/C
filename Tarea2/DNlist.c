typedef int tElem;

typedef struct node{
    tElem inicio;
    tElem final;
    struct node* next;
    struct node* prev;
}tNode;

typedef struct{
    unsigned int size;
    unsigned int pos;
    int totalByte;
    tNode* head;
    tNode* tail;
    tNode* curr;
}tList;

void initList(tList* L){
    L->curr=L->tail=L->head=(tNode*)malloc(sizeof(tNode));
    L->size=L->pos=L->totalByte=0;
}

tElem getValue(tList* L){
    if(L->curr == L->tail){
        return -1;
    }
    return L->curr->next->final - L->curr->next->inicio+1;
}

void next(tList* L){
    if(L->curr == L->tail){
        return;
    }
    L->curr=L->curr->next;
    L->pos++;
}

void prev(tList* L){
    if(L->curr == L->head){
        return;
    }
    L->pos--;
    L->curr=L->curr->prev;
}

unsigned int insert(tList* L,tElem inicial,tElem fin){
    tNode* aux=L->curr->next;
    L->curr->next=(tNode*)malloc(sizeof(tNode));
    L->curr->next->inicio=inicial;
    L->curr->next->final=fin;
    L->curr->next->next=aux;
    L->curr->next->prev=L->curr;
    if(L->curr == L->tail){
        L->tail=L->curr->next;
    }
    else{
        aux->prev=L->curr->next;
    }
    L->size++;
    L->totalByte=L->totalByte+getValue(L);
    return L->pos;
}

void clear(tList* L){
    tNode* aux;
    if(L->head == L->tail){
        return;
    }
    L->curr=L->head;
    while(L->curr->next!= L->tail){
        aux=L->curr->next->next;
        free((void*)L->curr->next);
        L->curr->next=aux;
    }
    free((void*)L->tail);
    L->tail=L->head;
    L->pos=L->size=0;
}

void deleteList(tList* L){
    clear(L);
    free((void*)L->head);
}

void moveToStart(tList* L){
    L->curr=L->head;
    L->pos=0;
}

void moveToEnd(tList* L){
    L->curr=L->tail;
}

unsigned int lenght(tList* L){
    return L->size;
}

unsigned int currPos(tList* L){
    return L->pos;
}

tElem erase(tList* L){
    if(L->curr == L->tail){
        return -1;
    }
    tNode* auxNode;
    L->totalByte=L->totalByte-getValue(L);
    tElem aux=L->curr->next->inicio;
    if(L->curr->next == L->tail){
        auxNode=L->tail;
        L->tail=L->tail->prev;
        free((void*)auxNode);
        L->pos--;
    }
    else{
        auxNode=L->curr->next;
        L->curr->next=L->curr->next->next;
        L->curr->next->prev=L->curr;
        free((void*)auxNode);
    }
    L->size--;
    return aux;
}

unsigned int append(tList* L,tElem inicio, tElem fin){
    unsigned int aux;
    moveToEnd(L);
    aux=insert(L,inicio,fin);
    return aux;
}

int moveToPos(tList* L,unsigned int position){
    if(position > L->size){
        return -1;
    }
    else if( L->pos < position){
        while(L->pos!=position){
            L->curr=L->curr->next;
            L->pos++;
        }
    }
    else{
        while(L->pos != position){
            L->curr=L->curr->prev;
            L->pos--;
        }
    }
    return 1;
}

tElem frontValue(tList* L){
    if(L->curr == L->tail){
        return -1;
    }
    return L->curr->next->inicio;
}

tElem endValue(tList* L){
    if(L->curr == L->tail){
        return -1;
    }
    return L->curr->next->final;
}

void swap(tList* L,int val){
    L->curr->next->inicio=L->curr->next->inicio+val;
    if(L->curr->next->inicio == L->curr->next->final+1){
        erase(L);
    }
}

int byte(tList* L){
    return L->totalByte;
}

void unite(tList* L){
    if(L->curr->next != L->tail){
        if(L->curr->next->final == L->curr->next->next->inicio-1){
            L->curr->next->next->inicio=L->curr->next->inicio;
            erase(L);
            unite(L);
        }
    }
    else if(L->curr->next->prev != L->head ){
        prev(L);
        unite(L);
    }
}
