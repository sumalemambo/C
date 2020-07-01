#include <stdio.h>
#include <stdlib.h>
#include "DNlist.c"

int main(){

    int M,N;
    FILE* fp = fopen("test22.dat","r");
    FILE* fs = fopen("test22.out","w");
    if(fp != NULL){
        fscanf(fp, "%d %d ",&M,&N);
        if(M <= 0 || N <= 0){
            printf("ERROR: El numero M y/o N dentro del archivo es/son cero o negativo");
            exit(1);
        }
        else{

            tList MM;
            tList FM;
            int value;
            initList(&MM);
            initList(&FM);
            insert(&MM,1,M);
            char check;
            char str[7];
            unsigned int laux1;
            unsigned int laux2;
            int True;

            for(int i = 0 ; i < N; i++){

                fscanf(fp,"%c",&check);
                laux1=lenght(&MM);
                laux2=lenght(&FM);

                if(check == 'm'){

                    True=0;
                    fscanf(fp,"%6s",str);
                    fscanf(fp,"%d ",&value);
                    moveToStart(&MM);

                    for(unsigned int k = 0 ; k < laux1 ; k++){
                        if( getValue(&MM) >= value){

                            fprintf(fs,"Bloque de %d bytes asignado a partir del byte %d\n",value,frontValue(&MM));
                            append(&FM,frontValue(&MM),value+frontValue(&MM)-1);
                            swap(&MM,value);
                            True=1;
                            break;
                        }
                        next(&MM);
                    }
                    if(True == 0){
                        fprintf(fs,"Bloque de %d bytes NO puede ser asignado\n",value);
                    }
                    
                }
                else{

                    fscanf(fp,"%5s",str);
                    fscanf(fp,"%d ",&value);
                    moveToStart(&FM);

                    for(unsigned int k = 0; k < laux2 ;k++){
                        if(frontValue(&FM) == value){

                            fprintf(fs,"Bloque de %d bytes liberado\n",getValue(&FM));
                            moveToStart(&MM);

                            for(unsigned int l = 0; l < laux1; l++){
                                if(frontValue(&MM) > value){
                                    break;
                                }
                                next(&MM);
                            }
                            insert(&MM,frontValue(&FM),endValue(&FM));
                            erase(&FM);
                            unite(&MM);
                            break;
                        }
                        next(&FM);
                    }
                }
            }

            laux2=lenght(&FM);
            if(laux2 > 0){
                fprintf(fs,"Quedaron %d bloques sin liberar (%d bytes)",laux2,byte(&FM));
            }
            else{
                fprintf(fs,"Toda la memoria dinámica pedida fue liberada");
            }

            deleteList(&MM);
            deleteList(&FM);
            fclose(fp);
            fclose(fs);
        }
    }
    else{
        printf("ERROR: El archivo no existe");
        exit(1);
    }
    return 0;
}
