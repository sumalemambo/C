#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "DLList2.c"

int main(){
    /* tList L;
    initList(&L);
    for(int i = 0; i < 10; i++){
        insert(&L,i);
        next(&L);
    }
    moveToStart(&L);
    for(int i = 0; i < 10; i++){
        next(&L); 
    }
        0 1 2 3 4 5 6 7 8 9
        1 2 3 4 5 6 7 8 9 10

        0 1 2 3 4 5 6 7 8 9
        9 8 7 6 5 4 3 2 1 0

    for(int i = 0; i < 10; i++){
        prev(&L); 
    }
    erase(&L);
    for(int i = 0 ; i < 9; i++){
        printf("%d",erase(&L));
    }
    clear(&L);
    deleteList(&L);
    */

    //File work
    FILE* fp = fopen("test22.dat","r");
    if(fp != NULL){

        int M,N;
        int Val;
        char Op[7];

        fscanf(fp,"%d\n%d",&M,&N);
        if(M <= 0 || N<=0){
            printf("ERROR : El valor M o el valor N del archivo es cero o negativo.\n");
            exit(1);
        }

        tList LM;
        initList(&LM);
        insert(&LM,1,M);
        tList LN;
        initList(&LN);

        while (fscanf(fp,"%s ",&Op,1) == 1){
            if(Op[0] == "m"){
                moveToStart(&LM);
                for(int i = 0 ; i < lenght(&LM); i++){
                    if(getValue(&LM) >= Val){
                        printf("%d ",LM.curr->inicio);
                        printf("%d \n",LM.curr->final);
                        append(&LN,frontValue(&LM),frontValue(&LM)+Val);
                        swap(&LM,Val);
                        printf("%d ",LN.curr->inicio);
                        printf("%d \n",LN.curr->final);
                        printf("%d ",LM.curr->inicio);
                        printf("%d \n",LM.curr->final);
                        break;
                    }
                    next(&LM);
                }
            }
            else if(Op == "free"){

            }
            else{
                printf("Operacion no valida\n");
            }
        }
        fclose(fp);
        deleteList(&LM);
        deleteList(&LN);
    }
    else{
        printf("El archivo no existe.\n"); //Placeholder
    }
}
