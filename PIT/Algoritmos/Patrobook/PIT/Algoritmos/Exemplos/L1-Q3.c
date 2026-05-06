#include <stdio.h>

int main() {
    float valor, desconto, valor_desconto, total;

    printf("Insira o valor: ");
    scanf("%f", &valor);

    printf("Insira o percentual de desconto oferecido: ");
    scanf("%f", &desconto);

    valor_desconto = valor * (desconto/100);
    total = valor - valor_desconto;

    printf("O valor do desconto é de: %.2f\n", valor_desconto);
    printf("O valor total com o desconto é de: %.2f\n", total);

    return 0;
}