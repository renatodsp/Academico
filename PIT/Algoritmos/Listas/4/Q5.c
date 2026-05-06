#include <stdio.h>

int main() {
    int idade;
    int maior, menor;
    float soma = 0;

    printf("Idade da pessoa 1: ");
    scanf("%d", &idade);
    maior = idade;
    menor = idade;
    soma = idade;

    for (int i = 2; i <= 20; i++) {
        printf("Idade da pessoa %d: ", i);
        scanf("%d", &idade);
        soma += idade;
        if (idade > maior) maior = idade;
        if (idade < menor) menor = idade;
    }

    printf("\nIdade da pessoa mais velha: %d\n", maior);
    printf("Idade da pessoa mais nova: %d\n", menor);
    printf("Media das idades: %.2f\n", soma / 20);

    return 0;
}
