#include <stdio.h>
int main(){
    int *u,d;
    u=&d;
    int *p;
    p=u;
    printf("%d\n",p);
    printf("%d\n",u);
    printf("%d",&d);
    return 0;
}