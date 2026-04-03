#include <stdio.h>

int main() {
    int n1, n2, result;

    printf("Insira o primeiro numero: ");
    scanf("%d", &n1);

    printf("Insira o segundo numero: ");
    scanf("%d", &n2);

    result = n1 + n2;

    if (result > 50) {
        printf("%d\n", result);
    }

    return 0;
}