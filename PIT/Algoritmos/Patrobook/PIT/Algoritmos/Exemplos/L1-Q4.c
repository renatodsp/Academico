#include <stdio.h>

int main() {
    float n1, n2, n3;
    float aux, media;
    printf("Digite a primeira nota: ");
    scanf("%f", &n1);
    printf("Digite a segunda nota: ");
    scanf("%f", &n2);
    printf("Digite a terceira nota: ");
    scanf("%f", &n3);


    if (n1<n2) {
        aux = n1;
        n1 = n2;
        n2 = aux;
    }
    
    if (n1<n3) {
        aux = n1;
        n1 = n3;
        n3 = aux;
    }
    
    if (n2<n3) {
        aux = n2;
        n2 = n3;
        n3 = aux;
    }

    media = (n1+n2+n3) / 3;

    printf("A média das notas é de: %.2f \n", media);
    printf("%.2f, %.2f, %.2f", n1, n2, n3);
    return 0;
}