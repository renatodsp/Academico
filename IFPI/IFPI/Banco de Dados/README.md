# 📚 Banco de Dados — Publicações

Script SQL completo para o exercício de banco de dados relacional sobre publicações literárias.

## 📋 Descrição

O banco **publicacoes** modela um sistema de gerenciamento de publicações com controle de livros, autores, editoras, assuntos e nacionalidades. O script inclui:

- **Criação** do banco e das 6 tabelas com chaves primárias, únicas e estrangeiras
- **Inserção** de dados de exemplo em todas as tabelas
- **75 consultas SQL** cobrindo desde filtros simples até subconsultas e junções complexas

## 🗂️ Estrutura do Banco

```
publicacoes
├── NACIONALIDADE (codigo PK, pais)
├── ASSUNTO       (codigo PK, descricao)
├── EDITORA       (codigo PK, cnpj UNIQUE, nome)
├── AUTOR         (codigo PK, nome, passaporte UNIQUE, datanascimento, nacionalidade_codigo FK)
├── LIVRO         (codigo PK, isbn UNIQUE, titulo, preco, datalancamento, assunto_codigo FK, editora_codigo FK)
└── AUTOR_LIVRO   (autor_codigo PK/FK, livro_codigo PK/FK)
```

### Diagrama de Relacionamentos

```
NACIONALIDADE 1──────N AUTOR
ASSUNTO       1──────N LIVRO
EDITORA       1──────N LIVRO
AUTOR         N──────N LIVRO  (via AUTOR_LIVRO)
```

## 🔑 Convenções de Chaves

| Tipo              | Descrição                                    | Exemplos                              |
|-------------------|----------------------------------------------|---------------------------------------|
| **Primária (PK)** | Identifica unicamente cada registro          | `codigo` em todas as tabelas          |
| **Única (UK)**    | Garante valores sem repetição                | `cnpj`, `isbn`, `passaporte`          |
| **Estrangeira (FK)** | Referência entre tabelas                  | `nacionalidade_codigo`, `assunto_codigo`, `editora_codigo` |

## 📊 Dados Inseridos

| Tabela          | Registros |
|-----------------|-----------|
| NACIONALIDADE   | 5         |
| ASSUNTO         | 7         |
| EDITORA         | 5         |
| AUTOR           | 10        |
| LIVRO           | 20        |
| AUTOR_LIVRO     | 27        |

## 🔍 Consultas (1 a 75)

As consultas estão organizadas por tópicos:

| Faixa     | Tópico                                       |
|-----------|----------------------------------------------|
| 1–10      | Filtros básicos (`WHERE`, `LIKE`, `BETWEEN`, `IN`, `IS NULL`) |
| 11–16     | Funções de agregação (`COUNT`, `SUM`, `AVG`, `MAX`, `MIN`)    |
| 17–24     | Agrupamento e filtro de grupos (`GROUP BY`, `HAVING`)          |
| 25–33     | Consultas sobre autores e junções                              |
| 34–40     | Funções de data, cálculos e `DISTINCT`                         |
| 41–47     | Ordenação, alias e funções de string                           |
| 48–55     | Junções (`JOIN`, `LEFT JOIN`, `COALESCE`)                      |
| 56–63     | Consultas com múltiplas junções                                |
| 64–70     | Subconsultas e `LEFT JOIN` avançado                            |
| 71–75     | Operadores lógicos compostos e `DELETE`                        |

## ⚙️ Como Executar

### Pré-requisitos

- **MySQL** 5.7+ ou **MariaDB** 10.3+ instalado

### Execução via terminal

```bash
# Acessar o MySQL
mysql -u root -p

# Executar o script completo
source /caminho/para/Exercicio04.sql;
```

### Execução via importação

```bash
mysql -u root -p < Exercicio04.sql
```

### Usando ferramentas gráficas

Abra o arquivo `Exercicio04.sql` em qualquer cliente SQL:
- **MySQL Workbench**
- **DBeaver**
- **phpMyAdmin**
- **HeidiSQL**

## ⚠️ Observações

- A **consulta 75** executa um `DELETE` — ela remove editoras sem livros associados. Execute-a por último ou separadamente.
- A **consulta 7** usa `CURDATE()` e pode retornar resultados diferentes dependendo da data de execução.
- Os dados inseridos são exemplos didáticos e foram planejados para que a maioria das consultas retorne resultados relevantes.

## 📁 Arquivo

| Arquivo           | Descrição                                      |
|-------------------|-------------------------------------------------|
| `Exercicio04.sql` | Script completo (criação, inserção, consultas) |
| `README.md`       | Este documento                                  |

---

**Disciplina:** Banco de Dados · **Instituição:** IFPI
