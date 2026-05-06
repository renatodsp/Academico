#include <stdio.h>

int main(){
    int n1;

    printf("Digite um numero: ");
    scanf("%d", &n1);

    if (n1 % 7 == 0) {
        printf("É Multiplo de 7.");
    }else {
        printf ("Não é multiplo de 7.");
    }
    
    return 0;
}