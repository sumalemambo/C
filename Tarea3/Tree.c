#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int key, rep;
}dato;

typedef dato elem;

typedef struct node{
    elem info;
    struct node* left;
    struct node* right;
}binNode;

typedef struct{
    int size;
    binNode* root;
}binTree;

void initTree(binTree* T){
    T->root = NULL;
    T->size=0;
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
    T->size=0;
}

binNode* insertHelp(binNode* nodo,elem data){
    if(nodo == NULL){
        nodo=(binNode*)malloc(sizeof(binNode));
        nodo->info=data;
        nodo->left=NULL;
        nodo->right=NULL;
    }
    else if(nodo->info.key > data.key){
        nodo->left=insertHelp(nodo->left,data);
    }
    else{
        nodo->right=insertHelp(nodo->right,data);
    }
    return nodo;
}

int findHelp(binNode* nodo,elem data){
    if(nodo == NULL){
        return 0;
    }
    else if(nodo->info.key > data.key){
        return findHelp(nodo->left,data);
    }
    else if(nodo->info.key == data.key){
        nodo->info.rep += data.rep;
        return 1;
    }
    else{
        return findHelp(nodo->right,data);
    }
}

int find(binTree* T,elem data){
    return findHelp(T->root,data);
}

void insert(binTree* T,elem data){
    T->root=insertHelp(T->root,data);
    T->size++;
}


void PreOrderHelp(binNode* nodo){
    if(nodo == NULL){
        return;
    }
    printf("--(%d , %d)--\n",nodo->info.key,nodo->info.rep);
    PreOrderHelp(nodo->left);
    PreOrderHelp(nodo->right);
}

void PreOrder(binTree* T){
    PreOrderHelp(T->root);
}

/*
void main(){
    binTree T;
    initTree(&T);
    elem d;
    for (int i = 0; i < 10; i++)
    {
        printf("Ingrese una key:");
        scanf("%d %d", &d.key, &d.rep);
        if(find(&T, d) == 1){
            continue;
        }
        else{
            insert(&T, d);
        }
    }
    PreOrder(&T);
    clearTree(&T);
}
*/
