#include <stdio.h>

int main(){
    int idade;

    printf("Insira a idade: ");
    scanf("%d", &idade);

    if (idade <18) {
        printf("Menor de idade.\n");
    }else if (idade>=65) {
        printf("Maior que 65 anos.\n");
    }else {
        printf("Maior de idade.\n");
    }

    return 0;
}