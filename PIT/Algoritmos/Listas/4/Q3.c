#include <stdio.h>

int main(){
    int contador = 0;
    int numero;

    while(1){
        printf("Insira um numero: ");
        scanf("%d", &numero);
        if (numero == 0) {
            break;
        }else if (numero >=100 && numero <=200) {
            contador ++;
        }
    }
    printf("Os números contados foram: %d\n", contador);
    return 0;
}