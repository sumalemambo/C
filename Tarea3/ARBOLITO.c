typedef struct{
    int key, rep;
}dato;

typedef struct node{
    dato info;
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

binNode* insertHelp(binNode* nodo,dato buy){
    if(nodo == NULL){
        nodo=(binNode*)malloc(sizeof(binNode));
        nodo->info=buy;
        nodo->left=NULL;
        nodo->right=NULL;
    }
    else if(nodo->info.key > buy.key){
        nodo->left=insertHelp(nodo->left,buy);
    }
    else{
        nodo->right=insertHelp(nodo->right,buy);
    }
    return nodo;
}

int findHelp(binNode* nodo,dato buy){
    if(nodo == NULL){
        return 0;
    }
    else if(nodo->info.key > buy.key){
        return findHelp(nodo->left,buy);
    }
    else if(nodo->info.key == buy.key){
        nodo->info.rep += buy.rep;
        return 1;
    }
    else{
        return findHelp(nodo->right,buy);
    }
}

int find(binTree* T,dato buy){
    return findHelp(T->root,buy);
}

void insert(binTree* T,dato buy){
    T->root=insertHelp(T->root,buy);
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
