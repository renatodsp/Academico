# Relatório — Patrobook: Simulador de Rede Social

**Disciplina:** Algoritmos, Estruturas de Dados e Programação  
**Instituição:** Piauí Instituto de Tecnologia (PIT)  
**Professor:** Joselito Junior

---

## 1. Introdução

O **Patrobook** é um sistema que simula funcionalidades básicas de uma rede social, desenvolvido em linguagem C (padrão C99). O projeto tem como objetivo consolidar conceitos de *structs*, ponteiros, listas encadeadas, modularização e gerenciamento dinâmico de memória.

O nome "Patrobook" é uma referência lúdica ao Facebook, combinando "Patro" (de patroa/patrão, gíria regional) com "book", criando uma identidade única para o projeto.

---

## 2. Estruturas de Dados

### 2.1 Lista Encadeada de Usuários

A estrutura principal do sistema é uma **lista simplesmente encadeada** de usuários. Cada nó (`NoUsuario`) contém:

- `id` (inteiro): identificador único, atribuído automaticamente de forma incremental
- `nome` (string de até 100 caracteres): nome completo do usuário
- `idade` (inteiro): idade do usuário
- `amigos` (ponteiro para `NoAmigo`): cabeça da lista encadeada de amigos
- `num_amigos` (inteiro): contador de amigos para consulta rápida
- `prox` (ponteiro para `NoUsuario`): próximo usuário na lista

A escolha por lista encadeada (em vez de vetor fixo) permite inserções e remoções em tempo O(n) sem necessidade de realocação de memória, além de não impor um limite máximo fixo de usuários.

### 2.2 Lista Encadeada de Amigos

Cada usuário possui sua própria lista encadeada de amigos (`NoAmigo`), onde cada nó armazena apenas o `id` do amigo e um ponteiro para o próximo. As amizades são **bidirecionais**: ao criar uma amizade entre A e B, o sistema insere B na lista de A e A na lista de B.

### 2.3 Estrutura de Controle

A `ListaUsuarios` funciona como controlador central, mantendo:
- Ponteiro para a cabeça da lista
- Contagem total de usuários
- Próximo ID disponível (para garantir unicidade)

---

## 3. Lógica dos Módulos

### 3.1 `patrobook.h` — Definições Globais
Contém todas as definições de structs, constantes, macros de cores ANSI para a interface estilizada e a função utilitária `limpar_buffer()`.

### 3.2 `usuario.c` — Gerenciamento de Usuários
- **`adicionar_usuario`**: aloca dinamicamente um novo nó, atribui ID incremental e insere no final da lista
- **`remover_usuario`**: localiza o usuário, percorre todos os outros para remover referências de amizade, libera a lista de amigos do usuário e o próprio nó
- **`buscar_usuario`**: busca linear por ID, retornando ponteiro ou NULL
- **`listar_perfis`**: percorre toda a lista exibindo dados formatados com cores ANSI
- **`liberar_lista`**: percorre e libera todos os nós de usuários e suas respectivas listas de amigos

### 3.3 `rede.c` — Gerenciamento de Amizades
- **`criar_amizade`**: valida (auto-amizade, existência, duplicidade) e cria vínculo bidirecional
- **`remover_amizade`**: valida e remove o vínculo de ambas as listas
- **`listar_amigos`**: percorre a lista de amigos exibindo nome e ID de cada um
- **`ja_sao_amigos`**: verifica se um ID existe na lista de amigos de um usuário

### 3.4 `persistencia.c` — Armazenamento em Arquivo
Implementa salvamento e carregamento em formato texto estruturado:
- Primeira linha: total de usuários e próximo ID
- Para cada usuário: dados (id, idade, nº de amigos), nome (linha separada) e IDs dos amigos
- O carregamento reconstrói a lista encadeada sem depender da função `adicionar_usuario`, preservando os IDs originais

### 3.5 `main.c` — Interface e Menu Principal
Implementa a interface textual estilizada com:
- Arte ASCII do logotipo "Patrobook"
- Menu colorido com emojis e bordas estilizadas usando caracteres Unicode
- Cores ANSI para feedback visual (verde = sucesso, vermelho = erro, amarelo = aviso)
- Fluxos interativos para cada operação com validação de entrada

---

## 4. Dificuldades Encontradas

1. **Gerenciamento de buffer de entrada**: a combinação de `scanf` e `fgets` requer limpeza cuidadosa do buffer stdin para evitar leituras indesejadas de caracteres residuais

2. **Remoção em cascata de amizades**: ao remover um usuário, é necessário percorrer todos os demais para remover referências ao usuário excluído, resultando em complexidade O(n × m)

3. **Preservação de IDs no carregamento**: ao carregar dados do arquivo, os IDs originais precisam ser mantidos, exigindo inserção direta na lista sem usar a função padrão de adição

4. **Compatibilidade de caracteres Unicode**: caracteres de desenho de caixa (╔═╗) e emojis podem não renderizar corretamente em todos os terminais, sendo necessário considerar fallbacks

---

## 5. Conclusão

O Patrobook atende a todos os requisitos funcionais e técnicos especificados, implementando uma rede social funcional com lista encadeada, modularização adequada, tratamento de erros e liberação completa de memória. Os bônus de persistência em arquivo e interface estilizada (tanto textual em C quanto gráfica em Python/Flask) agregam valor significativo ao projeto.
