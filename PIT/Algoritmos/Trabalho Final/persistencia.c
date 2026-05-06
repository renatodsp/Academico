/*
 * persistencia.c
 * Implementacao das funcoes de armazenamento persistente em arquivo.
 * Formato do arquivo:
 *   Linha 1: <total_usuarios> <proximo_id>
 *   Para cada usuario:
 *     Linha: <id> <idade> <num_amigos>
 *     Linha: <nome_completo>
 *     Linha: <id_amigo1> <id_amigo2> ... (ou vazio se sem amigos)
 */

#include "persistencia.h"

/* Salva todos os dados da rede em arquivo texto */
int salvar_dados(ListaUsuarios *lista, const char *arquivo) {
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL) {
        fprintf(stderr, "Erro: nao foi possivel abrir o arquivo %s para escrita.\n", arquivo);
        return 0;
    }

    /* Cabecalho: total de usuarios e proximo ID */
    fprintf(fp, "%d %d\n", lista->total, lista->prox_id);

    /* Percorrer todos os usuarios */
    NoUsuario *atual = lista->cabeca;
    while (atual != NULL) {
        /* Dados do usuario */
        fprintf(fp, "%d %d %d\n", atual->id, atual->idade, atual->num_amigos);
        fprintf(fp, "%s\n", atual->nome);

        /* Lista de amigos */
        NoAmigo *amigo = atual->amigos;
        while (amigo != NULL) {
            fprintf(fp, "%d", amigo->id);
            if (amigo->prox != NULL) {
                fprintf(fp, " ");
            }
            amigo = amigo->prox;
        }
        fprintf(fp, "\n");

        atual = atual->prox;
    }

    fclose(fp);
    return 1;
}

/* Carrega os dados de um arquivo texto para a lista */
int carregar_dados(ListaUsuarios *lista, const char *arquivo) {
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL) {
        return 0; /* Arquivo nao encontrado (primeira execucao) */
    }

    int total, prox_id;
    if (fscanf(fp, "%d %d", &total, &prox_id) != 2) {
        fclose(fp);
        return -1; /* Erro de leitura */
    }

    /* Consumir o '\n' restante apos fscanf */
    int c;
    while ((c = fgetc(fp)) != '\n' && c != EOF)
        ;

    lista->prox_id = prox_id;
    char linha[256];

    for (int i = 0; i < total; i++) {
        int id, idade, num_amigos;

        /* Ler dados do usuario */
        if (fscanf(fp, "%d %d %d", &id, &idade, &num_amigos) != 3) {
            fclose(fp);
            return -1;
        }
        /* Consumir o '\n' restante */
        while ((c = fgetc(fp)) != '\n' && c != EOF)
            ;

        /* Ler nome completo */
        char nome[MAX_NOME];
        if (fgets(nome, MAX_NOME, fp) == NULL) {
            fclose(fp);
            return -1;
        }
        /* Remover '\n' do final do nome */
        size_t len = strlen(nome);
        if (len > 0 && nome[len - 1] == '\n') {
            nome[len - 1] = '\0';
        }

        /* Criar o usuario diretamente na lista (sem usar adicionar_usuario
         * para preservar o ID original) */
        NoUsuario *novo = (NoUsuario *)malloc(sizeof(NoUsuario));
        if (novo == NULL) {
            fclose(fp);
            return -1;
        }

        novo->id = id;
        strncpy(novo->nome, nome, MAX_NOME - 1);
        novo->nome[MAX_NOME - 1] = '\0';
        novo->idade = idade;
        novo->amigos = NULL;
        novo->num_amigos = 0;
        novo->prox = NULL;

        /* Inserir no final da lista */
        if (lista->cabeca == NULL) {
            lista->cabeca = novo;
        } else {
            NoUsuario *ultimo = lista->cabeca;
            while (ultimo->prox != NULL) {
                ultimo = ultimo->prox;
            }
            ultimo->prox = novo;
        }
        lista->total++;

        /* Ler amigos */
        if (fgets(linha, sizeof(linha), fp) != NULL) {
            /* Remover '\n' */
            len = strlen(linha);
            if (len > 0 && linha[len - 1] == '\n') {
                linha[len - 1] = '\0';
            }

            /* Parsear IDs de amigos separados por espaco */
            if (strlen(linha) > 0) {
                char *token = strtok(linha, " ");
                while (token != NULL) {
                    int amigo_id = atoi(token);
                    if (amigo_id > 0) {
                        NoAmigo *no_amigo = (NoAmigo *)malloc(sizeof(NoAmigo));
                        if (no_amigo != NULL) {
                            no_amigo->id = amigo_id;
                            no_amigo->prox = novo->amigos;
                            novo->amigos = no_amigo;
                            novo->num_amigos++;
                        }
                    }
                    token = strtok(NULL, " ");
                }
            }
        }
    }

    fclose(fp);
    return 1;
}
