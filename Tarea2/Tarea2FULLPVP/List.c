typedef struct Node{
    struct Node* next;
    struct Node* prev;
    int inByte;
    int endByte;
}node;

typedef struct{
    int size;
    int byte;
    node* head;
    node* curr;
    node* tail;
}list;

int endValue(list* L){
    if(L->curr == L->tail){
        return -1;
    }
    return L->curr->next->endByte;
}
/*****
* TipoFunción: int ;NombreFunción: endValue
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: int;Descripción retorno: 
*****/

void prev(list* L){
    if(L->curr == L->head){
        return;
    }
    L->curr = L->curr->prev;
}
/*****
* TipoFunción: void ;NombreFunción: prev
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void next(list* L){
    if(L->curr == L->tail){
        return;
    }
    L->curr = L->curr->next;
}
/*****
* TipoFunción: void ;NombreFunción: next
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

int frontValue(list* L){
    if(L->curr == L->tail){
        return -1;
    }
    return L->curr->next->inByte;
}
/*****
* TipoFunción: int ;NombreFunción: frontValue
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: int;Descripción retorno: 
*****/

int getValue(list* L){
    if(L->head == L->tail || L->tail == L->curr){
        return -1;
    }
    return L->curr->next->endByte + 1 - L->curr->next->inByte;
}
/*****
* TipoFunción: void ;NombreFunción: getValue
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void initList(list* L){
    L->curr = L->tail = L->head=(node*)malloc(sizeof(node));
    L->byte = L->size = 0;
}
/*****
* TipoFunción: void ;NombreFunción: initList
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

int bytes(list* L){
    return L->byte;
}
/*****
* TipoFunción: int ;NombreFunción: byte
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: int;Descripción retorno: 
*****/

void moveToStart(list* L){
    L->curr = L->head;
}
/*****
* TipoFunción: void ;NombreFunción: moveToStart
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void insert(list* L,int byte1,int byte2){
    node* aux = L->curr->next;
    L->curr->next = (node*)malloc(sizeof(node));
    L->curr->next->inByte = byte1;
    L->curr->next->endByte = byte2;
    L->curr->next->next = aux;
    if(L->curr == L->tail){
        L->tail = L->curr->next;
    }
    else{
        aux->prev = L->curr->next;
    }
    L->curr->next->prev=L->curr;
    L->size++;
    L->byte+=getValue(L);
}
/*****
* TipoFunción: void ;NombreFunción: insert
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list,int,int;NombreParámetro: L,byte1,byte2
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

int lenght(list* L){
    return L->size;
}
/*****
* TipoFunción: int ;NombreFunción: lenght
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: int;Descripción retorno: 
*****/

void clear(list* L){
    if(L->head == L->tail){
        return;
    }
    moveToStart(L);
    node* aux;
    while(L->curr->next!= L->tail){
        aux=L->curr->next->next;
        free((void*)L->curr->next);
        L->curr->next = aux;
    }
    free((void*)L->tail);
    L->curr = L->tail = L->head;
    L->byte = L->size = 0;
}
/*****
* TipoFunción: void ;NombreFunción: clear
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void deleteList(list* L){
    clear(L);
    free((void*)L->head);
}
/*****
* TipoFunción: void ;NombreFunción: deleteList
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void erase(list* L){
    if(L->curr == L->tail){
        return;
    }
    else if(L->head->next == L->tail){
        L->byte-=getValue(L);
        free((void*)L->curr->next);
        L->tail = L->curr = L->head;
    }
    else{
        L->byte-=getValue(L);
        node* aux = L->curr->next->next; 
        if(L->curr->next == L->tail){
            L->tail = L->curr->next->prev;
            free((void*)L->curr->next);        
        }
        else{
            aux->prev = L->curr->next->prev;
            free((void*)L->curr->next);
        }
        L->curr->next=aux;

    }
    L->size--;

}
/*****
* TipoFunción: void ;NombreFunción: erase
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void swap(list* L1,list* L2,int byte){
    insert(L2,frontValue(L1),frontValue(L1)+byte-1);
    if(L1->curr->next->inByte+byte == L1->curr->next->endByte+1){
        erase(L1);
    }
    else{
        L1->curr->next->inByte+=byte;
    }
}
/*****
* TipoFunción: void ;NombreFunción: swap
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list,list,int;NombreParámetro: L1,L2,byte
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void find(list* L,int byte){
    moveToStart(L);
    for(int i = lenght(L);i--;){
        if(byte == frontValue(L)){
            break;
        }
        next(L);
    }
}
/*****
* TipoFunción: void ;NombreFunción: find
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list,int;NombreParámetro: L,byte
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void findAlloc(list* L,int byte){
    moveToStart(L);
    for(int i = lenght(L);i--;){
        if(byte < frontValue(L)){
            break;
        }
        next(L);
    }
}
/*****
* TipoFunción: void ;NombreFunción: findAlloc
******
* Resumen Función
* 
******
* Input:
* tipoParámetra: list,int;NombreParámetro: L,byte
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/

void erase2(list* L){
    if(L->curr == L->tail){
        return;
    }
    else if(L->head->next == L->tail){
        free((void*)L->curr->next);
        L->tail = L->curr = L->head;
    }
    else{
        node* aux = L->curr->next->next; 
        if(L->curr->next == L->tail){
            L->tail = L->curr->next->prev;
            free((void*)L->curr->next);        
        }
        else{
            aux->prev = L->curr->next->prev;
            free((void*)L->curr->next);
        }
        L->curr->next=aux;

    }
    L->size--;

}

void check(list* L){
    if(L->curr->next != L->tail){
        if(L->curr->next->next->inByte-1 == L->curr->next->endByte){
            L->curr->next->next->inByte = L->curr->next->inByte;
            erase2(L);
            check(L);
            return;
        }
    }
    if(L->curr->next->prev != L->head && L->curr!=L->head){
        if(L->curr->next->prev->endByte == L->curr->next->inByte-1){
            prev(L);
            check(L);
            return;
        }
    }
    
    
}
/*****
* TipoFunción: void ;NombreFunción: getcheckValue
******
* Resumen Función
* Obtiene valor del nodo 
******
* Input:
* tipoParámetra: list;NombreParámetro: L
******
* Returns:
* TipoRetorno: ;Descripción retorno: 
*****/
