#include <stdio.h>

int main() {
    int idade;

    printf("Insira sua idade: ");
    scanf("%d", &idade);

    if (idade<=7 && idade>=5) {
        printf("Infantil A\n");
    }
    if (idade<=10 && idade>=8) {
        printf("Infantil B\n");
    }
    if (idade<=13 && idade>=11) {
        printf("Juvenil A\n");
    }
    if (idade<=17 && idade>=14) {
        printf("Juvenil B\n");
    }else{
        printf("Maiores de 18 anos");
    }
    
    return 0;
}