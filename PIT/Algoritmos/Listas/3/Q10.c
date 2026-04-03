#include <stdio.h>
#include <math.h>

int main() {
    double A, B, C, delta, x1, x2;

    printf("Digite os valores de A, B e C: ");
    if (scanf("%lf %lf %lf", &A, &B, &C) != 3) {
        printf("Erro na leitura dos dados.\n");
        return 1;
    }

    if (A == 0) {
        printf("Não é equação do segundo grau\n");
    } else {
        delta = pow(B, 2) - 4 * A * C;

        if (delta > 0) {
            x1 = (-B + sqrt(delta)) / (2 * A);
            x2 = (-B - sqrt(delta)) / (2 * A);
            printf("As raízes reais são: x1 = %.2lf e x2 = %.2lf\n", x1, x2);
        } else if (delta == 0) {
            x1 = -B / (2 * A);
            printf("A única raiz real é: x = %.2lf\n", x1);
        } else {
            printf("Não existem raízes reais\n");
        }
    }

    return 0;
}
