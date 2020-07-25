#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int Key,Cant;
    char Name[31];
}data;

typedef struct nodo{
    struct data *dat;
    struct nodo *Izquierdo;
    struct nodo *Derecho;
}nDatos;

void InitData(data* d,int Key,int c){
    d->Cant = c;
    d->Key = Key;
    for(int x = 0; x <31;x++){
        d->Name[x] = ' ';
    }
}

void FreeData(data* d){
    free(d);
}

int GetKey(data* d){
    return(d->Key);
}

int GetCant(data* d){
    return(d->Cant);
}

void AddCant(data* d,int c){
    d->Cant += c;
}

typedef struct {
    nDatos *raiz;
    int Size;
}tAbb;


void InitTree(tAbb* t){
    t->raiz = NULL;
    t->Size = 0;
}

void ClearHelp(nDatos* d){
    if(d == NULL){
        free(d);
    }
    else
    {
        ClearHelp(d->Derecho);
        ClearHelp(d->Izquierdo);
        free(d);
    }
    
}

void Clear(tAbb* t){
    ClearHelp(t->raiz);
    t->raiz = NULL;
    t->Size = 0;
}

int InsertHelp(nDatos* n,nDatos* d){
    int f = 1;
    if(n == NULL){
        n = d;
    }
    else
    {
        if(GetKey(d->dat) < GetKey(n->dat)){
            f += InsertHelp(n->Izquierdo,d);
        }
        else if(GetKey(d->dat) > GetKey(n->dat)){
            f += InsertHelp(n->Derecho,d);
        }
        else{
            AddCant(n->dat,GetCant(d->dat));
            f = 0;
        }
    }
    return f;
}

void Insert(tAbb* t,nDatos* dat){
    if(t->raiz == NULL){
        t->raiz = dat;
        t->Size ++;
    }
    else
    {
        t->Size += InsertHelp(t->raiz,dat);
    }
    
}

int FindHelp(nDatos* d,int k){
    if(d == NULL){
        return 0;
    }
    else
    {
        if(GetKey(d->dat) == k){
            return 1;
        }
        else{
            if(k < GetKey(d->dat)){
                return(FindHelp(d->Izquierdo,k));
            }
            else
            {
                return(FindHelp(d->Derecho,k));
            }
        }       
    }
}


int Find(tAbb* t,int Key){
    return(FindHelp(t->raiz,Key));
}

int PrintHelp(nDatos* d){
    if(d == NULL){
        printf(" ");
    }
    else
    {
        if(d->Izquierdo != NULL){
            PrintHelp(d->Izquierdo);
        }
        else if(d->Derecho != NULL)
        {
            PrintHelp(d->Derecho);
        }
        else
        {
            printf("%d",GetKey(d->dat));
        }
    printf("\n");
    }
}

void PrintTree(tAbb* t){
    PrintHelp(t->raiz);
}

void main(){
    tAbb* t;
    data* d;
    InitTree(t);
    for(int x = 0;x < 10;x++){
        int k,c;
        scanf("key: %d\n",&k);
        scanf("Cant: %d\n",&c);
        InitData(d,k,c);
        Insert(t,d);
        FreeData(d);
    }
    PrintTree(t);
}