#include <stdio.h>

int main(){
    int n1, n2, n3;

    printf("Insira o primeiro numero: ");
    scanf("%d", &n1);
    
    printf("Insira o segundo numero: ");
    scanf("%d", &n2);
    
    printf("Insira o terceiro numero: ");
    scanf("%d", &n3);
    

    if (n1>n2 && n1>n3) {
        printf("%d\n", n1);
    }else if (n2>n1 && n2>n3) {
        printf("%d\n", n2);
    }else {
        printf("%d\n", n3);
    }

    return 0;
}