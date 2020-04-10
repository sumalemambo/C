#include <stdio.h>
int main() {
    char x; //Char es un caracter (letra), se almacenan como numeros ASCII
    unsigned y; //entero sin signo
    int j; //entero con o sin signo
    float k; //Un flotante con hasta 6 digitos de precision despues de la coma!
    double d; //Double , 12 digitos despues de la coma
    d=102.122355244123;
    y=104; //Aqui le entrego un numero que con %c me entrega su caracter correspondiente en ASCII
    x='h'; // Aqui le entrego un caracters que con %d me entrega su valor en la tabla ASCII, aunque %d tambien entrega numeros
    k=217.232131; // Para entregar un float no uso %d, uso %f
    printf("El numero 104 representa al caracter %c en el codigo ASCII \n",y);
    printf("La letra h corresponde al numero %d en el codigo ASCII\n",x);
    printf("En resumidas cuentas 104 = %c y h = %d \n",y,x);
    printf("Este es un flotante con 6 digitos de precision despues de la coma %f \n",k);// Aqui uso %f
    printf("El tamaño de un unsigned es de %d bytes\n",sizeof(unsigned));
    printf("El tamaño de un int es de %d bytes\n",sizeof(int));
    printf("El tamaño de un char es de %d bytes\n",sizeof(char));
    printf("El tamaño de un float es de %d bytes\n",sizeof(float));
    printf("El tamaño de un short es de %d bytes\n",sizeof(short));
    printf("El tamaño de un long es de %d bytes\n",sizeof(long));
    printf("Un double float seria  %lf\n",d);
    j=(int)k; //Cast aqui uso int por que no le puedo cambiar asignacion a j por tanto hago que k sea un int para que calze
    printf("Un flotante como entero seria %d",j);
    return(0);
}
