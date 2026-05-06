/*
 * persistencia.h
 * Declaracoes das funcoes de armazenamento persistente em arquivo.
 */

#ifndef PERSISTENCIA_H
#define PERSISTENCIA_H

#include "patrobook.h"

/* Salva todos os dados da rede em arquivo texto.
 * Retorna: 1 = sucesso, 0 = erro */
int salvar_dados(ListaUsuarios *lista, const char *arquivo);

/* Carrega os dados de um arquivo texto para a lista.
 * Retorna: 1 = sucesso, 0 = arquivo nao encontrado, -1 = erro de leitura */
int carregar_dados(ListaUsuarios *lista, const char *arquivo);

#endif /* PERSISTENCIA_H */
