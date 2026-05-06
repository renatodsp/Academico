/*
 * usuario.c
 * Implementacao das funcoes de gerenciamento de usuarios.
 * Utiliza lista encadeada simples para armazenar os usuarios.
 */

#include "usuario.h"

/* Inicializa a lista de usuarios com valores padrao */
void inicializar_lista(ListaUsuarios *lista) {
    lista->cabeca = NULL;
    lista->total = 0;
    lista->prox_id = 1;
}

/* Adiciona um novo usuario ao final da lista encadeada */
NoUsuario* adicionar_usuario(ListaUsuarios *lista, const char *nome, int idade) {
    if (nome == NULL || strlen(nome) == 0) {
        return NULL;
    }
    if (idade <= 0 || idade > 150) {
        return NULL;
    }

    NoUsuario *novo = (NoUsuario *)malloc(sizeof(NoUsuario));
    if (novo == NULL) {
        fprintf(stderr, "Erro: falha ao alocar memoria para usuario.\n");
        return NULL;
    }

    novo->id = lista->prox_id++;
    strncpy(novo->nome, nome, MAX_NOME - 1);
    novo->nome[MAX_NOME - 1] = '\0';
    novo->idade = idade;
    novo->amigos = NULL;
    novo->num_amigos = 0;
    novo->prox = NULL;

    /* Inserir no final da lista para manter ordem de criacao */
    if (lista->cabeca == NULL) {
        lista->cabeca = novo;
    } else {
        NoUsuario *atual = lista->cabeca;
        while (atual->prox != NULL) {
            atual = atual->prox;
        }
        atual->prox = novo;
    }

    lista->total++;
    return novo;
}

/* Libera a lista de amigos de um usuario */
static void liberar_amigos(NoAmigo *amigo) {
    NoAmigo *temp;
    while (amigo != NULL) {
        temp = amigo;
        amigo = amigo->prox;
        free(temp);
    }
}

/* Remove um amigo especifico da lista de amigos de um usuario */
static void remover_amigo_da_lista(NoUsuario *usuario, int id_amigo) {
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
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

/* Remove um usuario pelo ID.
 * Tambem remove todas as referencias a ele nas listas de amigos de outros usuarios. */
int remover_usuario(ListaUsuarios *lista, int id) {
    NoUsuario *atual = lista->cabeca;
    NoUsuario *anterior = NULL;
    NoUsuario *alvo = NULL;

    /* Encontrar o usuario na lista */
    while (atual != NULL) {
        if (atual->id == id) {
            alvo = atual;
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }

    if (alvo == NULL) {
        return 0; /* Usuario nao encontrado */
    }

    /* Remover este usuario da lista de amigos de todos os outros */
    NoUsuario *percorre = lista->cabeca;
    while (percorre != NULL) {
        if (percorre->id != id) {
            remover_amigo_da_lista(percorre, id);
        }
        percorre = percorre->prox;
    }

    /* Liberar a lista de amigos do usuario sendo removido */
    liberar_amigos(alvo->amigos);

    /* Remover o no da lista principal */
    if (anterior == NULL) {
        lista->cabeca = alvo->prox;
    } else {
        anterior->prox = alvo->prox;
    }

    free(alvo);
    lista->total--;
    return 1;
}

/* Busca um usuario pelo ID na lista */
NoUsuario* buscar_usuario(ListaUsuarios *lista, int id) {
    NoUsuario *atual = lista->cabeca;
    while (atual != NULL) {
        if (atual->id == id) {
            return atual;
        }
        atual = atual->prox;
    }
    return NULL;
}

/* Exibe todos os perfis cadastrados com formatacao estilizada */
void listar_perfis(ListaUsuarios *lista) {
    if (lista->total == 0) {
        printf("\n  %s%s Nenhum perfil cadastrado.%s\n", BOLD, YELLOW, RESET);
        return;
    }

    printf("\n  %s%s Total de perfis: %d%s\n", BOLD, CYAN, lista->total, RESET);
    printf("  %s──────────────────────────────────────────%s\n", DIM, RESET);

    NoUsuario *atual = lista->cabeca;
    while (atual != NULL) {
        printf("  %s%s┌─ Perfil #%d ─────────────────────────────┐%s\n",
               BOLD, PB_AZUL, atual->id, RESET);
        printf("  %s│%s  👤 Nome:   %s%-28s%s %s│%s\n",
               PB_AZUL, RESET, BOLD, atual->nome, RESET, PB_AZUL, RESET);
        printf("  %s│%s  🎂 Idade:  %-28d %s│%s\n",
               PB_AZUL, RESET, atual->idade, PB_AZUL, RESET);
        printf("  %s│%s  👥 Amigos: %-28d %s│%s\n",
               PB_AZUL, RESET, atual->num_amigos, PB_AZUL, RESET);
        printf("  %s└──────────────────────────────────────────┘%s\n",
               PB_AZUL, RESET);
        atual = atual->prox;
    }
}

/* Libera toda a memoria da lista de usuarios e suas listas de amigos */
void liberar_lista(ListaUsuarios *lista) {
    NoUsuario *atual = lista->cabeca;
    NoUsuario *temp;

    while (atual != NULL) {
        temp = atual;
        atual = atual->prox;
        liberar_amigos(temp->amigos);
        free(temp);
    }

    lista->cabeca = NULL;
    lista->total = 0;
    lista->prox_id = 1;
}
