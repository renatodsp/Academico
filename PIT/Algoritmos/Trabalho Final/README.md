# 🌐 Patrobook - Rede Social

**Trabalho Final** — Algoritmos, Estruturas de Dados e Programação  
Piauí Instituto de Tecnologia (PIT) — Prof. Joselito Junior

---

## 📖 Descrição

O **Patrobook** é um simulador de rede social desenvolvido em linguagem C, que permite cadastrar usuários, gerenciar amizades bidirecionais e listar perfis. O sistema utiliza **listas encadeadas** como estrutura de dados principal, garantindo alocação dinâmica eficiente e flexível.

Como bônus, o projeto inclui:
- 💾 **Armazenamento persistente** em arquivo texto
- 🎨 **Interface textual estilizada** com cores ANSI e arte ASCII
- 🌐 **Interface gráfica web** em Python (Flask) com design inspirado no Facebook

---

## 🗂️ Estrutura do Projeto

```
Trabalho Final/
├── main.c              # Ponto de entrada e interface de menu
├── usuario.h           # Declarações - gerenciamento de usuários
├── usuario.c           # Implementação - gerenciamento de usuários
├── rede.h              # Declarações - gerenciamento de amizades
├── rede.c              # Implementação - gerenciamento de amizades
├── persistencia.h      # Declarações - armazenamento em arquivo
├── persistencia.c      # Implementação - armazenamento em arquivo
├── patrobook.h         # Definições globais, structs e macros
├── Makefile            # Automação de compilação
├── README.md           # Este arquivo
├── relatorio.md        # Relatório do projeto
└── interface/          # Interface web (bônus)
    ├── app.py          # Servidor Flask (API REST)
    ├── requirements.txt
    ├── templates/
    │   └── index.html  # Interface web (SPA)
    └── static/
        └── style.css   # Estilos CSS
```

---

## 🔧 Compilação e Execução

### Requisitos
- **GCC** com suporte a C99 ou superior
- **Python 3.8+** e **pip** (apenas para a interface web)

### Compilação do Programa em C

**Opção 1 — Usando Make:**
```bash
make
```

**Opção 2 — Compilação direta:**
```bash
gcc -Wall -Wextra -O2 -std=c99 main.c usuario.c rede.c persistencia.c -o patrobook
```

### Execução
```bash
./patrobook
```

### Limpeza dos arquivos compilados
```bash
make clean
```

---

## 🌐 Interface Web (Bônus)

### Instalação
```bash
cd interface
pip install -r requirements.txt
```

### Execução
```bash
python app.py
```

Acesse no navegador: **http://localhost:5000**

---

## 🎮 Funcionalidades

| Nº | Funcionalidade       | Descrição                                                  |
|----|---------------------|------------------------------------------------------------|
| 1  | Adicionar Perfil    | Cadastra usuário com ID automático, nome e idade           |
| 2  | Remover Perfil      | Remove usuário e todas as suas amizades automaticamente    |
| 3  | Criar Amizade       | Cria vínculo bidirecional (com validações)                 |
| 4  | Remover Amizade     | Desfaz vínculo entre dois usuários                         |
| 5  | Listar Amigos       | Exibe nome e ID dos amigos de um usuário                   |
| 6  | Listar Perfis       | Exibe todos os perfis com ID, nome, idade e nº de amigos   |
| 7  | Salvar Dados        | Salva manualmente os dados em arquivo                      |
| 0  | Sair                | Salva dados e libera toda a memória alocada                |

---

## 🏗️ Estruturas de Dados

O projeto utiliza **listas simplesmente encadeadas** para:
- **Lista de Usuários**: cada nó (`NoUsuario`) contém os dados do perfil e um ponteiro para o próximo
- **Lista de Amigos**: cada nó (`NoAmigo`) armazena o ID de um amigo e um ponteiro para o próximo

```c
typedef struct NoAmigo {
    int id;
    struct NoAmigo *prox;
} NoAmigo;

typedef struct NoUsuario {
    int id;
    char nome[100];
    int idade;
    NoAmigo *amigos;
    int num_amigos;
    struct NoUsuario *prox;
} NoUsuario;
```

---

## ✅ Validações Implementadas

- ❌ Nome vazio ou inválido
- ❌ Idade fora do intervalo (1–150)
- ❌ Amizade com o próprio usuário
- ❌ Amizade duplicada
- ❌ Operações com IDs inexistentes
- ✅ Liberação completa de memória ao sair
- ✅ Salvamento automático antes de encerrar

---

## 👨‍💻 Autor

Desenvolvido como Trabalho Final da disciplina de Algoritmos e Estruturas de Dados — PIT.
