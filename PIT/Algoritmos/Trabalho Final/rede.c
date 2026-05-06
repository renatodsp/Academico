/*
 * rede.c
 * Implementacao das funcoes de gerenciamento de amizades.
 * As amizades sao bidirecionais e armazenadas em listas encadeadas.
 */

#include "rede.h"
#include "usuario.h"

/* Verifica se um usuario ja possui determinado amigo */
int ja_sao_amigos(NoUsuario *usuario, int id_amigo) {
    NoAmigo *atual = usuario->amigos;
    while (atual != NULL) {
        if (atual->id == id_amigo) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

/* Adiciona um ID na lista de amigos de um usuario (funcao interna) */
static int adicionar_amigo_lista(NoUsuario *usuario, int id_amigo) {
    NoAmigo *novo = (NoAmigo *)malloc(sizeof(NoAmigo));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para amizade.\n");
        return 0;
    }
    novo->id = id_amigo;
    novo->prox = usuario->amigos;
    usuario->amigos = novo;
    usuario->num_amigos++;
    return 1;
}

/* Remove um ID da lista de amigos de um usuario (funcao interna) */
static int remover_amigo_lista(NoUsuario *usuario, int id_amigo) {
    NoAmigo *atual = usuario->amigos;
    NoAmigo *anterior = NULL;

    while (atual != NULL) {
        if (atual->id == id_amigo) {
            if (anterior == NULL) {
                usuario->amigos = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            usuario->num_amigos--;
            return 1;
        }
        anterior = atual;
        atual = atual->prox;
    }
    return 0;
}

/* Cria uma amizade bidirecional entre dois usuarios */
int criar_amizade(ListaUsuarios *lista, int id1, int id2) {
    /* Verificar auto-amizade */
    if (id1 == id2) {
        printf("  %s%s ✗ Erro: voce nao pode ser amigo de si mesmo!%s\n",
               BOLD, RED, RESET);
        return 0;
    }

    /* Buscar ambos os usuarios */
    NoUsuario *u1 = buscar_usuario(lista, id1);
    NoUsuario *u2 = buscar_usuario(lista, id2);

    if (u1 == NULL) {
        printf("  %s%s ✗ Erro: usuario com ID %d nao encontrado.%s\n",
               BOLD, RED, id1, RESET);
        return 0;
    }
    if (u2 == NULL) {
        printf("  %s%s ✗ Erro: usuario com ID %d nao encontrado.%s\n",
               BOLD, RED, id2, RESET);
        return 0;
    }

    /* Verificar amizade duplicada */
    if (ja_sao_amigos(u1, id2)) {
        printf("  %s%s ✗ Erro: %s e %s ja sao amigos!%s\n",
               BOLD, YELLOW, u1->nome, u2->nome, RESET);
        return 0;
    }

    /* Criar amizade bidirecional */
    if (!adicionar_amigo_lista(u1, id2) || !adicionar_amigo_lista(u2, id1)) {
        return 0;
    }

    return 1;
}

/* Remove a amizade entre dois usuarios */
int remover_amizade(ListaUsuarios *lista, int id1, int id2) {
    if (id1 == id2) {
        printf("  %s%s ✗ Erro: IDs identicos.%s\n", BOLD, RED, RESET);
        return 0;
    }

    NoUsuario *u1 = buscar_usuario(lista, id1);
    NoUsuario *u2 = buscar_usuario(lista, id2);

    if (u1 == NULL) {
        printf("  %s%s ✗ Erro: usuario com ID %d nao encontrado.%s\n",
               BOLD, RED, id1, RESET);
        return 0;
    }
    if (u2 == NULL) {
        printf("  %s%s ✗ Erro: usuario com ID %d nao encontrado.%s\n",
               BOLD, RED, id2, RESET);
        return 0;
    }

    if (!ja_sao_amigos(u1, id2)) {
        printf("  %s%s ✗ Erro: %s e %s nao sao amigos.%s\n",
               BOLD, YELLOW, u1->nome, u2->nome, RESET);
        return 0;
    }

    remover_amigo_lista(u1, id2);
    remover_amigo_lista(u2, id1);

    return 1;
}

/* Lista os amigos de um usuario especifico */
void listar_amigos(ListaUsuarios *lista, int id) {
    NoUsuario *usuario = buscar_usuario(lista, id);

    if (usuario == NULL) {
        printf("  %s%s ✗ Erro: usuario com ID %d nao encontrado.%s\n",
               BOLD, RED, id, RESET);
        return;
    }

    printf("\n  %s%s👥 Amigos de %s (ID: %d)%s\n",
           BOLD, CYAN, usuario->nome, usuario->id, RESET);
    printf("  %s──────────────────────────────────────────%s\n", DIM, RESET);

    if (usuario->num_amigos == 0) {
        printf("  %s%s Nenhum amigo adicionado ainda.%s\n", DIM, YELLOW, RESET);
        return;
    }

    NoAmigo *amigo = usuario->amigos;
    int count = 1;
    while (amigo != NULL) {
        NoUsuario *perfil = buscar_usuario(lista, amigo->id);
        if (perfil != NULL) {
            printf("  %s%s %d.%s 👤 %s%-20s%s  (ID: %d)\n",
                   PB_AZUL, BOLD, count, RESET, BOLD, perfil->nome, RESET, perfil->id);
        }
        amigo = amigo->prox;
        count++;
    }

    printf("\n  %s Total: %d amigo(s)%s\n", DIM, usuario->num_amigos, RESET);
}
