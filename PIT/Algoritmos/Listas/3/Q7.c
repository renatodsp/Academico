#include <stdio.h>

int main() {
    int n1;
    
    printf("Insira um numero de 1 a 7: ");
    scanf("%d", &n1);

    if (n1 == 1) {
        printf("DOMINGO");
    }
    else if (n1 == 2) {
        printf("SEGUNDA-FEIRA");
    }
    else if (n1 == 3) {
        printf("TERCA-FEIRA");
    }
    else if (n1 == 4) {
        printf("QUARTA-FEIRA");
    }
    else if (n1 == 5) {
        printf("QUINTA-FEIRA");
    }
    else if (n1 == 6) {
        printf("SEXTA-FEIRA");
    }
    else if (n1 == 7) {
        printf("SABADO");
    }
    else
    {
        printf("Insira um número válido.");
    }
    
}