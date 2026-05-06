#include <stdio.h>

int main() {
    float n1, n2, n3, media;
    char aluno[50];
    

    printf("Insira o nome do aluno: ");
    scanf("%49s", aluno);

    printf("Insira a primeira nota: ");
    scanf(" %f", &n1);
    
    printf("Insira a segunda nota: ");
    scanf(" %f", &n2);
    
    printf("Insira a terceira nota: ");
    scanf(" %f", &n3);


    media = (n1 + n2 + n3) / 3;

    printf("\n--- Resultado Final --- \n");
    printf("Aluno: %s\n", aluno);
    printf("Primeira nota: %.2f\n", n1);
    printf("Segunda nota: %.2f\n", n2);
    printf("Terceira nota: %.2f\n", n3);
    printf("Sua média é de: %.2f\n", media);

    if (media >= 7.0) {
        printf("Status: APROVADO\n");
    } else if (media < 4.0) {
        printf("Status: REPROVADO\n");
    } else {
        printf("Status: EXAME FINAL\n");
    }

    return 0;
}