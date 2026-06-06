# Patrobook - Simulador de Rede Social em C

Este projeto consiste no desenvolvimento de um simulador de rede social simplificado chamado **Patrobook**, como trabalho final da disciplina de **Algoritmo, Estruturas de Dados e Programação** do Piauí Instituto de Tecnologia (PIT), ministrada pelo Professor Joselito Junior.

---

## 🤖 Orientações para Assistentes de IA (Contexto de Desenvolvimento)

> **ATENÇÃO ASSISTENTE:** 
> 1. **Linguagem Obrigatória:** O projeto deve ser desenvolvido estritamente em **C (padrão C99 ou superior)** devido aos critérios de avaliação acadêmica (ponteiros, structs, gerenciamento de memória manual).
> 2. **Abordagem Pedagógica:** O usuário deseja aprender a lógica por trás de cada implementação. **Não forneça códigos prontos diretamente**, a menos que explicitamente solicitado. Apresente algoritmos, explicações conceituais, pseudocódigos ou guias passo a passo para forçar a reflexão e a escrita ativa do código.
> 3. **Estado Atual do Projeto:** Consulte a seção [Progresso do Projeto](#progresso-do-projeto) abaixo para saber em qual etapa estamos trabalhando no momento.
> 4. **Registro de Dúvidas:** Sempre que o usuário tiver uma dúvida conceitual, o assistente deve registrá-la e explicá-la detalhadamente no arquivo [duvidas_relatorio.md](file:///c:/Academico/PIT/Algoritmos/Trabalho%20Final/duvidas_relatorio.md) para auxiliar na confecção do relatório acadêmico.

---

## 📋 Requisitos e Diretrizes do Projeto

### Requisitos Funcionais
- **Cadastrar Usuário:** ID único, nome, idade e lista dinâmica de amigos.
- **Remover Usuário:** Excluir usuário e, obrigatoriamente, remover seu vínculo de todas as listas de amizades da rede.
- **Criar Amizade:** Relação bidirecional (se A é amigo de B, B é amigo de A). Sem duplicatas ou amizades consigo mesmo.
- **Remover Amizade:** Romper o vínculo bidirecional entre dois usuários cadastrados.
- **Listar Amigos:** Exibir nome e ID dos amigos de um usuário específico.
- **Listar Todos os Perfis:** Exibir ID, nome, idade e quantidade de amigos de todos os cadastrados.
- **Sair:** Desalocar absolutamente toda a memória alocada dinamicamente antes de encerrar o programa.

### Recursos Extras (Pontos de Bônus)
- **Persistência em Arquivos (+1.0):** Salvar e carregar dados de um arquivo de texto ao iniciar/encerrar o programa.
- **Interface Textual Estilizada (+1.0):** Implementar menus organizados utilizando códigos de cores ANSI no console.

---

## 🏗️ Arquitetura de Módulos (Organização de Arquivos)

O sistema é dividido em três módulos para garantir boas práticas de modularização:

1. **Módulo Usuário (`usuario.h` e `usuario.c`)**
   - Responsável pela estrutura interna de um perfil individual e manipulação direta de seus dados (alocação do usuário, inserção/remoção de ponteiros de amigos no seu vetor pessoal).
2. **Módulo Rede Social (`rede.h` e `rede.c`)**
   - Responsável pelo gerenciador global. Controla o vetor de todos os usuários da rede, busca por ID, lógica de amizade bidirecional e escrita/leitura de arquivos.
3. **Módulo Principal (`main.c`)**
   - Controla o fluxo do programa, exibe a interface de texto (menu de opções) e faz as chamadas das funções dos módulos anteriores.

---

## 📈 Progresso do Projeto

Marque com `[x]` as etapas concluídas e indique com `▶️` onde o trabalho está pausado atualmente.

- [ ] **Fase 1: Módulo do Usuário**
  - [ ] Criar estrutura `Usuario` em `usuario.h`.
  - [ ] Implementar `criar_usuario` e `destruir_usuario` em `usuario.c`.
  - [ ] Implementar `adicionar_ponteiro_amigo` e `remover_ponteiro_amigo` em `usuario.c`.
- [ ] **Fase 2: Módulo da Rede Social**
  - [ ] Criar estrutura `RedeSocial` em `rede.h`.
  - [ ] Implementar cadastro, busca e remoção de usuários de forma global em `rede.c`.
  - [ ] Implementar funções de criar/remover amizade bidirecional em `rede.c`.
- [ ] **Fase 3: Persistência de Dados**
  - [ ] Implementar função para salvar dados em arquivo TXT.
  - [ ] Implementar função para ler dados do arquivo TXT e reconstruir a rede na inicialização.
- [ ] **Fase 4: Menu e Interface Estilizada (`main.c`)**
  - [ ] Implementar o loop do menu principal no terminal.
  - [ ] Estilizar a saída visual com formatações e cores ANSI.
- [ ] **Fase 5: Testes e Validação de Memória**
  - [ ] Testar cenários de erro (IDs duplicados, exclusão de usuários com amigos, etc.).
  - [ ] Validar a liberação de memória total (sem memory leaks).

---

## ⚙️ Compilação e Execução

O programa deve ser compilado utilizando o GCC com as seguintes flags de compilação:

```bash
gcc -Wall -Wextra -O2 main.c usuario.c rede.c -o patrobook