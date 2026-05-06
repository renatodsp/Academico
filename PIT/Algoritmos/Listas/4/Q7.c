#include <stdio.h>

int main() {
    int arvore, chute;
    int balas = 5;

    printf("=== JOGO DO MARCIANO ===\n");
    printf("Jogador 1: escolha a arvore (1 a 100) em que o marciano se esconde: ");
    scanf("%d", &arvore);

    /* Limpa a tela de forma simples para esconder a escolha */
    for (int i = 0; i < 50; i++) printf("\n");

    printf("Jogador 2: o marciano se escondeu! Voce tem %d balas.\n\n", balas);

    while (balas > 0) {
        printf("Balas restantes: %d. Atire em qual arvore? ", balas);
        scanf("%d", &chute);
        balas--;

        if (chute == arvore) {
            printf("ACERTOU! O marciano foi capturado na arvore %d!\n", arvore);
            return 0;
        } else if (balas == 0) {
            printf("Sem balas! O marciano escapou para Marte! Era a arvore %d.\n", arvore);
        } else if (chute < arvore) {
            printf("Errou! O marciano diz: estou mais para a DIREITA!\n\n");
        } else {
            printf("Errou! O marciano diz: estou mais para a ESQUERDA!\n\n");
        }
    }

    return 0;
}
