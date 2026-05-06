#include <stdio.h>

int main() {
    float A, B, C;

    printf("Insira os tres lados do triângulo: ");
    scanf("%f %f %f", &A, &B, &C);

    if (A < B + C && B < A + C && C < A + B) {
        printf("Os lados formam um triangulo ");
    
    
        /*Tipo de triangulo*/
        if (A == B && A == C) {
            printf("EQUILATERO");
        }else if (A == B|| A == C || B == C) {
            printf("ISOSCELES");
        }else {
            printf("ESCALENO");
        }
    }else {
        printf("OS LADOS NAO FORMAM UM TRIANGULO.");
    }

    return 0;
}