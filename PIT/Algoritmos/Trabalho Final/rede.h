/*
 * rede.h
 * Declaracoes das funcoes de gerenciamento de amizades na rede social.
 */

#ifndef REDE_H
#define REDE_H

#include "patrobook.h"

/* Verifica se dois usuarios ja sao amigos. Retorna 1 se sim, 0 se nao */
int ja_sao_amigos(NoUsuario *usuario, int id_amigo);

/* Cria amizade bidirecional entre dois usuarios.
 * Retorna: 1 = sucesso, 0 = erro (inexistente, duplicada, auto-amizade) */
int criar_amizade(ListaUsuarios *lista, int id1, int id2);

/* Remove amizade entre dois usuarios.
 * Retorna: 1 = sucesso, 0 = erro */
int remover_amizade(ListaUsuarios *lista, int id1, int id2);

/* Lista os amigos de um usuario especifico */
void listar_amigos(ListaUsuarios *lista, int id);

#endif /* REDE_H */
