#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Serve p manipular strings

struct Usuario {
    int id;
    char nome[50];
    int idade;
    struct Usuario**amigos;
    int nmr_amigos;
    int capacidade_amigos;
};

struct Usuario* criar_usuario(int id, const char *nome, int idade) {
    struct Usuario *novo = (struct Usuario*) malloc(sizeof(struct Usuario)); //malloc usado, limpar ao excluir usuário
    if (novo == NULL) {
        return NULL;
    }

    novo->id = id;
    novo->idade = idade;

    strncpy(novo->nome, nome, 49);
    novo->nome[49] = '\0';

    novo->nmr_amigos = 0;
    novo->capacidade_amigos = 8;

    novo->amigos = (struct Usuario**) malloc(8 * sizeof(struct Usuario*)); //malloc usado, limpar ao excluir usuário
    if (novo->amigos == NULL) {
        free(novo);
        return NULL;
    }
    
    return novo;
}

// ao usar o free, lembrar de limpar de dentro para fora. fznd o caminho inverso.
void destruir_usuario(struct Usuario *usuario) {
    if (usuario == NULL) {
        return;
    }
        free(usuario->amigos);
        free(usuario);
}



int main(){


    return 0;
}