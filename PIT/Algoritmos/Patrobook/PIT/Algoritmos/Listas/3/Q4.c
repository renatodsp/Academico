#include <stdio.h>

int main(){
    char sexo, nome[15];
    int idade;

    printf("Insira a idade: ");
    scanf("%d", &idade);

    printf("Insira o sexo(M ou F): ");
    scanf(" %c", &sexo);

    printf("Insira o nome: ");
    scanf(" %14s", nome);

if (sexo == 'F' && idade <25) {
    printf("%s, ACEITA", nome);
}else {
    printf("%s, NÃO ACEITO(A)", nome);
}

    return 0;
}