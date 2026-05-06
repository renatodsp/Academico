/*
 * usuario.h
 * Declaracoes das funcoes de gerenciamento de usuarios.
 */

#ifndef USUARIO_H
#define USUARIO_H

#include "patrobook.h"

/* Inicializa a lista de usuarios */
void inicializar_lista(ListaUsuarios *lista);

/* Adiciona um novo usuario a rede. Retorna ponteiro para o usuario criado ou NULL em caso de erro */
NoUsuario* adicionar_usuario(ListaUsuarios *lista, const char *nome, int idade);

/* Remove um usuario pelo ID. Retorna 1 em sucesso, 0 se nao encontrado */
int remover_usuario(ListaUsuarios *lista, int id);

/* Busca um usuario pelo ID. Retorna ponteiro ou NULL */
NoUsuario* buscar_usuario(ListaUsuarios *lista, int id);

/* Exibe todos os perfis cadastrados */
void listar_perfis(ListaUsuarios *lista);

/* Libera toda a memoria alocada pela lista */
void liberar_lista(ListaUsuarios *lista);

#endif /* USUARIO_H */
