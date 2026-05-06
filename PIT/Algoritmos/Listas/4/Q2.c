#include <stdio.h>

int main() {
    int soma = 0;
    int n;

    for(n = 25; n <= 525; n++){
        if (n % 2 == 0) {
            soma += n;
        }
    }

    printf("A soma dos numeros pares e: %d", soma);
    return 0;
}