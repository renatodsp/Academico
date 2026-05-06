#include <stdio.h>

int main() {
    char nome[50];
    int idade;
    float salario;

    for (int i = 1; i <= 20; i++) {
        printf("Pessoa %d:\n", i);
        printf("  Nome: ");
        scanf(" %[^\n]", nome);
        printf("  Idade: ");
        scanf("%d", &idade);
        printf("  Salario: ");
        scanf("%f", &salario);

        if (salario > 2000.0) {
            printf("  -> %s ganha mais de R$2000,00\n", nome);
        }
    }

    return 0;
}
