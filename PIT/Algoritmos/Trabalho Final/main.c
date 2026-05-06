/*
 * main.c
 * Ponto de entrada do Patrobook - Rede Social em C.
 * Interface textual estilizada com cores ANSI e arte ASCII.
 *
 * Trabalho Final - Algoritmos e Estruturas de Dados
 * Piauí Instituto de Tecnologia (PIT)
 */

#include "usuario.h"
#include "rede.h"
#include "persistencia.h"

/* ==================== FUNCOES DE INTERFACE ==================== */

/* Limpa a tela do terminal (compativel com Windows e Unix) */
static void limpar_tela(void) {
    #ifdef _WIN32
        system("cls");
    #else
        printf("\033[H\033[J");
    #endif
}

/* Exibe o logo do Patrobook em arte ASCII estilizada */
static void exibir_logo(void) {
    printf("\n");
    printf("  %s%s╔══════════════════════════════════════════════════╗%s\n", BOLD, PB_AZUL, RESET);
    printf("  %s%s║%s                                                  %s%s║%s\n", BOLD, PB_AZUL, RESET, BOLD, PB_AZUL, RESET);
    printf("  %s%s║%s   %s%s ____       _             _                 _  %s%s║%s\n", BOLD, PB_AZUL, RESET, BOLD, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s║%s   %s%s|  _ \\ __ _| |_ _ __ ___ | |__   ___   ___ | | __%s  %s║%s\n", BOLD, PB_AZUL, RESET, BOLD, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s║%s   %s%s| |_) / _` | __| '__/ _ \\| '_ \\ / _ \\ / _ \\| |/ /%s  %s║%s\n", BOLD, PB_AZUL, RESET, BOLD, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s║%s   %s%s|  __/ (_| | |_| | | (_) | |_) | (_) | (_) |   <%s   %s║%s\n", BOLD, PB_AZUL, RESET, BOLD, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s║%s   %s%s|_|   \\__,_|\\__|_|  \\___/|_.__/ \\___/ \\___/|_|\\_\\%s  %s║%s\n", BOLD, PB_AZUL, RESET, BOLD, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s║%s                                                  %s%s║%s\n", BOLD, PB_AZUL, RESET, BOLD, PB_AZUL, RESET);
    printf("  %s%s║%s     %s%s🌐 Conecte-se com quem importa!%s               %s║%s\n", BOLD, PB_AZUL, RESET, DIM, CYAN, RESET, PB_AZUL, RESET);
    printf("  %s%s║%s                                                  %s%s║%s\n", BOLD, PB_AZUL, RESET, BOLD, PB_AZUL, RESET);
    printf("  %s%s╚══════════════════════════════════════════════════╝%s\n", BOLD, PB_AZUL, RESET);
}

/* Exibe o menu principal com opcoes numeradas */
static void exibir_menu(void) {
    printf("\n");
    printf("  %s%s┌──────────────────────────────────────────┐%s\n", BOLD, PB_AZUL, RESET);
    printf("  %s%s│%s  %s%s MENU PRINCIPAL %s                        %s│%s\n", BOLD, PB_AZUL, RESET, BOLD, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s├──────────────────────────────────────────┤%s\n", BOLD, PB_AZUL, RESET);
    printf("  %s%s│%s                                          %s│%s\n", PB_AZUL, BOLD, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[1]%s 👤  Adicionar Perfil                %s│%s\n", PB_AZUL, BOLD, RESET, GREEN, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[2]%s 🗑️   Remover Perfil                 %s│%s\n", PB_AZUL, BOLD, RESET, RED, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[3]%s 🤝  Criar Amizade                   %s│%s\n", PB_AZUL, BOLD, RESET, CYAN, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[4]%s 💔  Remover Amizade                 %s│%s\n", PB_AZUL, BOLD, RESET, MAGENTA, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[5]%s 👥  Listar Amigos                   %s│%s\n", PB_AZUL, BOLD, RESET, YELLOW, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[6]%s 📋  Listar Perfis                   %s│%s\n", PB_AZUL, BOLD, RESET, BLUE, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[7]%s 💾  Salvar Dados                    %s│%s\n", PB_AZUL, BOLD, RESET, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s                                          %s│%s\n", PB_AZUL, BOLD, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s  %s[0]%s 🚪  Sair                            %s│%s\n", PB_AZUL, BOLD, RESET, DIM, RESET, PB_AZUL, RESET);
    printf("  %s%s│%s                                          %s│%s\n", PB_AZUL, BOLD, RESET, PB_AZUL, RESET);
    printf("  %s%s└──────────────────────────────────────────┘%s\n", BOLD, PB_AZUL, RESET);
    printf("\n  %s%s▶ Escolha uma opcao:%s ", BOLD, PB_AZUL, RESET);
}

/* Exibe mensagem de sucesso */
static void msg_sucesso(const char *msg) {
    printf("\n  %s%s ✓ %s%s\n", BOLD, GREEN, msg, RESET);
}

/* Exibe separador visual */
static void separador(void) {
    printf("\n  %s════════════════════════════════════════════%s\n", DIM, RESET);
}

/* Exibe titulo de secao */
static void titulo_secao(const char *titulo) {
    printf("\n  %s%s── %s ──%s\n\n", BOLD, CYAN, titulo, RESET);
}

/* Pressione Enter para continuar */
static void pausar(void) {
    printf("\n  %sPressione %sENTER%s%s para continuar...%s", DIM, BOLD, RESET, DIM, RESET);
    limpar_buffer();
}

/* ==================== FUNCOES DE OPERACAO ==================== */

/* Fluxo de adicao de novo perfil */
static void fluxo_adicionar(ListaUsuarios *lista) {
    titulo_secao("NOVO PERFIL");

    char nome[MAX_NOME];
    int idade;

    printf("  %s👤 Nome completo:%s ", BOLD, RESET);
    if (fgets(nome, MAX_NOME, stdin) == NULL) {
        return;
    }
    /* Remover newline */
    size_t len = strlen(nome);
    if (len > 0 && nome[len - 1] == '\n') {
        nome[len - 1] = '\0';
    }

    if (strlen(nome) == 0) {
        printf("  %s%s ✗ Erro: o nome nao pode ser vazio.%s\n", BOLD, RED, RESET);
        pausar();
        return;
    }

    printf("  %s🎂 Idade:%s ", BOLD, RESET);
    if (scanf("%d", &idade) != 1) {
        printf("  %s%s ✗ Erro: idade invalida.%s\n", BOLD, RED, RESET);
        limpar_buffer();
        pausar();
        return;
    }
    limpar_buffer();

    if (idade <= 0 || idade > 150) {
        printf("  %s%s ✗ Erro: idade deve ser entre 1 e 150.%s\n", BOLD, RED, RESET);
        pausar();
        return;
    }

    NoUsuario *novo = adicionar_usuario(lista, nome, idade);
    if (novo != NULL) {
        separador();
        printf("  %s%s ✓ Perfil criado com sucesso!%s\n", BOLD, GREEN, RESET);
        printf("  %s   ID atribuido: %s%d%s\n", DIM, BOLD, novo->id, RESET);
        printf("  %s   Nome: %s%s%s\n", DIM, BOLD, novo->nome, RESET);
        printf("  %s   Idade: %s%d%s\n", DIM, BOLD, novo->idade, RESET);
    } else {
        printf("  %s%s ✗ Erro ao criar perfil.%s\n", BOLD, RED, RESET);
    }
    pausar();
}

/* Fluxo de remocao de perfil */
static void fluxo_remover(ListaUsuarios *lista) {
    titulo_secao("REMOVER PERFIL");

    if (lista->total == 0) {
        printf("  %s%s Nenhum perfil cadastrado.%s\n", BOLD, YELLOW, RESET);
        pausar();
        return;
    }

    /* Mostrar perfis existentes para referencia */
    printf("  %sPerfis disponiveis:%s\n", DIM, RESET);
    NoUsuario *temp = lista->cabeca;
    while (temp != NULL) {
        printf("    %s[%d]%s %s\n", PB_AZUL, temp->id, RESET, temp->nome);
        temp = temp->prox;
    }
    printf("\n");

    int id;
    printf("  %s🗑️  ID do perfil a remover:%s ", BOLD, RESET);
    if (scanf("%d", &id) != 1) {
        printf("  %s%s ✗ Erro: ID invalido.%s\n", BOLD, RED, RESET);
        limpar_buffer();
        pausar();
        return;
    }
    limpar_buffer();

    NoUsuario *usuario = buscar_usuario(lista, id);
    if (usuario == NULL) {
        printf("  %s%s ✗ Erro: usuario com ID %d nao encontrado.%s\n",
               BOLD, RED, id, RESET);
        pausar();
        return;
    }

    char nome_removido[MAX_NOME];
    strncpy(nome_removido, usuario->nome, MAX_NOME - 1);
    nome_removido[MAX_NOME - 1] = '\0';

    if (remover_usuario(lista, id)) {
        separador();
        printf("  %s%s ✓ Perfil de \"%s\" removido com sucesso!%s\n",
               BOLD, GREEN, nome_removido, RESET);
        printf("  %s   Todas as amizades foram desfeitas automaticamente.%s\n",
               DIM, RESET);
    } else {
        printf("  %s%s ✗ Erro ao remover perfil.%s\n", BOLD, RED, RESET);
    }
    pausar();
}

/* Fluxo de criacao de amizade */
static void fluxo_criar_amizade(ListaUsuarios *lista) {
    titulo_secao("NOVA AMIZADE");

    if (lista->total < 2) {
        printf("  %s%s E necessario ter ao menos 2 perfis cadastrados.%s\n",
               BOLD, YELLOW, RESET);
        pausar();
        return;
    }

    /* Mostrar perfis existentes */
    printf("  %sPerfis disponiveis:%s\n", DIM, RESET);
    NoUsuario *temp = lista->cabeca;
    while (temp != NULL) {
        printf("    %s[%d]%s %s\n", PB_AZUL, temp->id, RESET, temp->nome);
        temp = temp->prox;
    }
    printf("\n");

    int id1, id2;
    printf("  %s🤝 ID do primeiro usuario:%s ", BOLD, RESET);
    if (scanf("%d", &id1) != 1) {
        printf("  %s%s ✗ Erro: ID invalido.%s\n", BOLD, RED, RESET);
        limpar_buffer();
        pausar();
        return;
    }

    printf("  %s🤝 ID do segundo usuario:%s ", BOLD, RESET);
    if (scanf("%d", &id2) != 1) {
        printf("  %s%s ✗ Erro: ID invalido.%s\n", BOLD, RED, RESET);
        limpar_buffer();
        pausar();
        return;
    }
    limpar_buffer();

    if (criar_amizade(lista, id1, id2)) {
        NoUsuario *u1 = buscar_usuario(lista, id1);
        NoUsuario *u2 = buscar_usuario(lista, id2);
        separador();
        printf("  %s%s ✓ Amizade criada!%s\n", BOLD, GREEN, RESET);
        if (u1 && u2) {
            printf("  %s   %s 🤝 %s%s\n", DIM, u1->nome, u2->nome, RESET);
        }
    }
    pausar();
}

/* Fluxo de remocao de amizade */
static void fluxo_remover_amizade(ListaUsuarios *lista) {
    titulo_secao("REMOVER AMIZADE");

    if (lista->total < 2) {
        printf("  %s%s Nao ha amizades para remover.%s\n", BOLD, YELLOW, RESET);
        pausar();
        return;
    }

    int id1, id2;
    printf("  %s💔 ID do primeiro usuario:%s ", BOLD, RESET);
    if (scanf("%d", &id1) != 1) {
        printf("  %s%s ✗ Erro: ID invalido.%s\n", BOLD, RED, RESET);
        limpar_buffer();
        pausar();
        return;
    }

    printf("  %s💔 ID do segundo usuario:%s ", BOLD, RESET);
    if (scanf("%d", &id2) != 1) {
        printf("  %s%s ✗ Erro: ID invalido.%s\n", BOLD, RED, RESET);
        limpar_buffer();
        pausar();
        return;
    }
    limpar_buffer();

    NoUsuario *u1 = buscar_usuario(lista, id1);
    NoUsuario *u2 = buscar_usuario(lista, id2);
    char n1[MAX_NOME] = "", n2[MAX_NOME] = "";
    if (u1) strncpy(n1, u1->nome, MAX_NOME - 1);
    if (u2) strncpy(n2, u2->nome, MAX_NOME - 1);

    if (remover_amizade(lista, id1, id2)) {
        separador();
        printf("  %s%s ✓ Amizade desfeita.%s\n", BOLD, GREEN, RESET);
        printf("  %s   %s 💔 %s%s\n", DIM, n1, n2, RESET);
    }
    pausar();
}

/* Fluxo de listagem de amigos */
static void fluxo_listar_amigos(ListaUsuarios *lista) {
    titulo_secao("LISTAR AMIGOS");

    if (lista->total == 0) {
        printf("  %s%s Nenhum perfil cadastrado.%s\n", BOLD, YELLOW, RESET);
        pausar();
        return;
    }

    /* Mostrar perfis para referencia */
    printf("  %sPerfis disponiveis:%s\n", DIM, RESET);
    NoUsuario *temp = lista->cabeca;
    while (temp != NULL) {
        printf("    %s[%d]%s %s (%d amigo%s)\n",
               PB_AZUL, temp->id, RESET, temp->nome,
               temp->num_amigos, temp->num_amigos != 1 ? "s" : "");
        temp = temp->prox;
    }
    printf("\n");

    int id;
    printf("  %s👥 ID do usuario:%s ", BOLD, RESET);
    if (scanf("%d", &id) != 1) {
        printf("  %s%s ✗ Erro: ID invalido.%s\n", BOLD, RED, RESET);
        limpar_buffer();
        pausar();
        return;
    }
    limpar_buffer();

    listar_amigos(lista, id);
    pausar();
}

/* Fluxo de listagem de perfis */
static void fluxo_listar_perfis(ListaUsuarios *lista) {
    titulo_secao("TODOS OS PERFIS");
    listar_perfis(lista);
    pausar();
}

/* Fluxo de salvamento manual */
static void fluxo_salvar(ListaUsuarios *lista) {
    if (salvar_dados(lista, ARQUIVO_DADOS)) {
        msg_sucesso("Dados salvos com sucesso!");
    } else {
        printf("  %s%s ✗ Erro ao salvar dados.%s\n", BOLD, RED, RESET);
    }
    pausar();
}

/* ==================== FUNCAO PRINCIPAL ==================== */

int main(void) {
    ListaUsuarios rede;
    inicializar_lista(&rede);

    /* Carregar dados salvos, se existirem */
    int resultado = carregar_dados(&rede, ARQUIVO_DADOS);
    if (resultado == 1) {
        /* Dados carregados - sera exibido apos limpar tela */
    } else if (resultado == -1) {
        fprintf(stderr, "Aviso: erro ao ler arquivo de dados.\n");
    }

    int opcao = -1;
    int dados_carregados = (resultado == 1);

    do {
        limpar_tela();
        exibir_logo();

        /* Notificacao de dados carregados (apenas na primeira vez) */
        if (dados_carregados) {
            printf("\n  %s%s 💾 %d perfil(is) carregado(s) do arquivo.%s\n",
                   DIM, GREEN, rede.total, RESET);
            dados_carregados = 0;
        }

        exibir_menu();

        if (scanf("%d", &opcao) != 1) {
            limpar_buffer();
            opcao = -1;
            continue;
        }
        limpar_buffer();

        limpar_tela();
        exibir_logo();

        switch (opcao) {
            case 1:
                fluxo_adicionar(&rede);
                break;
            case 2:
                fluxo_remover(&rede);
                break;
            case 3:
                fluxo_criar_amizade(&rede);
                break;
            case 4:
                fluxo_remover_amizade(&rede);
                break;
            case 5:
                fluxo_listar_amigos(&rede);
                break;
            case 6:
                fluxo_listar_perfis(&rede);
                break;
            case 7:
                fluxo_salvar(&rede);
                break;
            case 0:
                break;
            default:
                printf("\n  %s%s ✗ Opcao invalida! Tente novamente.%s\n",
                       BOLD, RED, RESET);
                pausar();
                break;
        }

    } while (opcao != 0);

    /* Salvar dados antes de sair */
    separador();
    printf("\n  %s💾 Salvando dados...%s\n", CYAN, RESET);
    salvar_dados(&rede, ARQUIVO_DADOS);

    /* Liberar toda a memoria alocada */
    printf("  %s🧹 Liberando memoria...%s\n", CYAN, RESET);
    liberar_lista(&rede);

    printf("\n  %s%s╔══════════════════════════════════════════════════╗%s\n", BOLD, PB_AZUL, RESET);
    printf("  %s%s║%s                                                  %s%s║%s\n", BOLD, PB_AZUL, RESET, BOLD, PB_AZUL, RESET);
    printf("  %s%s║%s   %s%sObrigado por usar o Patrobook! Ate logo! 👋%s     %s║%s\n", BOLD, PB_AZUL, RESET, BOLD, WHITE, RESET, PB_AZUL, RESET);
    printf("  %s%s║%s                                                  %s%s║%s\n", BOLD, PB_AZUL, RESET, BOLD, PB_AZUL, RESET);
    printf("  %s%s╚══════════════════════════════════════════════════╝%s\n\n", BOLD, PB_AZUL, RESET);

    return 0;
}
