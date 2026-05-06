/*
 * patrobook.h
 * Definicoes globais, structs e macros de estilizacao do Patrobook.
 * Trabalho Final - Algoritmos e Estruturas de Dados (PIT)
 */

#ifndef PATROBOOK_H
#define PATROBOOK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ======================= CONSTANTES ======================= */
#define MAX_NOME        100
#define ARQUIVO_DADOS   "patrobook.dat"
#define LARGURA_BOX     52

/* =================== CORES ANSI (Terminal) ================ */
#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define DIM         "\033[2m"

#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"
#define MAGENTA     "\033[35m"
#define CYAN        "\033[36m"
#define WHITE       "\033[37m"

#define BG_BLUE     "\033[44m"
#define BG_CYAN     "\033[46m"
#define BG_WHITE    "\033[47m"

#define PB_AZUL     "\033[38;5;33m"
#define PB_BG       "\033[48;5;33m"

/* =============== ESTRUTURAS DE DADOS =============== */

/* No de lista encadeada de amigos */
typedef struct NoAmigo {
    int id;
    struct NoAmigo *prox;
} NoAmigo;

/* No de lista encadeada de usuarios */
typedef struct NoUsuario {
    int id;
    char nome[MAX_NOME];
    int idade;
    NoAmigo *amigos;
    int num_amigos;
    struct NoUsuario *prox;
} NoUsuario;

/* Lista encadeada principal que armazena toda a rede */
typedef struct {
    NoUsuario *cabeca;
    int total;
    int prox_id;
} ListaUsuarios;

/* =============== FUNCOES UTILITARIAS =============== */

/* Limpa o buffer de entrada do stdin */
static inline void limpar_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

#endif /* PATROBOOK_H */
