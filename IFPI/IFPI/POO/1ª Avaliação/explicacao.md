# Explicação da Avaliação — Boleto Bancário

---

## `boleto.py` — A Classe

### O que é uma classe?
Uma classe é um molde para criar objetos. No caso, `Boleto` é o molde e cada boleto criado é um objeto diferente.

---

### Atributo de classe: `_contador`

```python
class Boleto:
    _contador = 0
```

Esse atributo pertence à **classe**, não a um objeto específico. Toda vez que um boleto é criado, ele é incrementado (`+1`), garantindo que cada boleto tenha um número único e automático. O `_` na frente indica que é um atributo **privado** (encapsulamento).

---

### O construtor `__init__`

```python
def __init__(self, nome_pagador, valor_original, data_vencimento):
```

O construtor é chamado automaticamente quando criamos um objeto. Ele recebe os dados necessários e faz as **validações** antes de criar o boleto:

- **Nome vazio** → lança `ValueError`
- **Valor zero ou negativo** → lança `ValueError`
- **Vencimento menor ou igual à emissão** → lança `ValueError`

A `data_emissao` é registrada automaticamente com `date.today()`, sem precisar ser passada pelo usuário.

#### Atributos imutáveis (não mudam depois de criados):
| Atributo | Descrição |
|---|---|
| `_numero` | Gerado pelo contador, único |
| `_nome_pagador` | Nome de quem vai pagar |
| `_valor_original` | Valor base do boleto |
| `_data_emissao` | Data de hoje na criação |

#### Atributos mutáveis (podem mudar):
| Atributo | Valor inicial | Descrição |
|---|---|---|
| `_data_vencimento` | Passada na criação | Prazo para pagar |
| `_data_pagamento` | `None` | Preenchida ao pagar |
| `_status` | `"em aberto"` | Estado atual do boleto |
| `_valor_final` | `0.00` | Calculado ao pagar |

---

### Encapsulamento com `@property`

O encapsulamento protege os atributos de serem acessados ou modificados diretamente de fora da classe. Usamos `_` nos atributos e `@property` para criar uma forma controlada de leitura e escrita.

#### Só leitura (sem setter) — atributos imutáveis:

```python
@property
def nome_pagador(self):
    return self._nome_pagador
```

Assim, `boleto.nome_pagador` funciona, mas `boleto.nome_pagador = "outro"` vai dar erro.

#### Leitura e escrita (com setter) — atributos mutáveis:

```python
@property
def data_vencimento(self):
    return self._data_vencimento

@data_vencimento.setter
def data_vencimento(self, nova_data):
    if nova_data <= self._data_emissao:
        raise ValueError("...")
    if self._status == "pago":
        raise ValueError("...")
    self._data_vencimento = nova_data
```

O setter valida antes de aceitar a mudança. Se o boleto já foi pago, não deixa alterar o vencimento.

#### O `status` tem lógica extra:

```python
@property
def status(self):
    if self._status == "em aberto" and date.today() > self._data_vencimento:
        self._status = "vencido"
    return self._status
```

Toda vez que alguém consulta o status, ele verifica automaticamente se o boleto venceu. Assim o status fica sempre atualizado.

---

### Método `consultar_valor_atualizado`

```python
def consultar_valor_atualizado(self, data_referencia=None):
```

Calcula quanto o boleto vale numa determinada data, aplicando as regras:

| Situação | Regra |
|---|---|
| Pagamento **3 ou mais dias antes** do vencimento | Desconto de **5%** |
| Pagamento **no prazo** (0 a 2 dias antes ou no dia) | Sem desconto, valor original |
| Pagamento **após** o vencimento | Multa de **2%** + juros de **0,03% por dia** de atraso |

**Exemplo:** Boleto de R$ 1.000, pago 10 dias atrasado:
- Multa: 1000 × 0,02 = R$ 20,00
- Juros: 1000 × 0,0003 × 10 = R$ 3,00
- **Total: R$ 1.023,00**

---

### Método `registrar_pagamento`

```python
def registrar_pagamento(self, data_pagamento=None):
```

Registra que o boleto foi pago. Ele:
1. Verifica se o boleto ainda pode ser pago (não pode se já estiver pago ou cancelado)
2. Verifica se a data de pagamento não é anterior à emissão
3. Salva a data de pagamento
4. Calcula e salva o `valor_final` usando `consultar_valor_atualizado`
5. Muda o status para `"pago"`

---

### Método `cancelar_boleto`

```python
def cancelar_boleto(self):
    if self._status == "pago":
        raise ValueError("nao pode cancelar boleto que ja foi pago")
    self._status = "cancelado"
```

Simples: muda o status para `"cancelado"`, mas bloqueia se o boleto já foi pago.

---

### `__str__` — representação do objeto

```python
def __str__(self):
    return f"Boleto {self._numero} | ..."
```

Quando fazemos `print(boleto)`, esse método é chamado automaticamente e exibe as informações do boleto de forma legível.

---

## `test_boleto.py` — Os Testes

Os testes usam o **Pytest**, que é uma biblioteca Python para testar se o código funciona corretamente. Cada função `test_` representa um cenário diferente.

### Como o Pytest funciona?

O Pytest encontra automaticamente qualquer função que começa com `test_` e a executa. Se o `assert` dentro dela for verdadeiro, o teste **passa**. Se for falso, o teste **falha**.

Para testar se um erro é lançado, usamos:
```python
with pytest.raises(ValueError):
    # código que deve dar erro aqui
```

---

### Testes implementados

#### `test_criar_boleto` — testa o construtor
Cria um boleto válido e verifica se os atributos iniciais estão corretos: nome, valor, status `"em aberto"` e pagamento `None`.

#### `test_boleto_valor_invalido` — testa validação do construtor
Verifica se o construtor lança `ValueError` quando o valor é negativo.

#### `test_pagamento_antecipado` — registrar_pagamento com desconto
Paga 5 dias antes do vencimento. Verifica se o status é `"pago"` e o valor final tem 5% de desconto (R$ 950,00 de R$ 1.000,00).

#### `test_pagamento_pontual` — registrar_pagamento no prazo
Paga no dia do vencimento. Verifica se o valor final é o original, sem desconto nem multa.

#### `test_pagamento_atrasado` — registrar_pagamento com multa e juros
Paga 10 dias depois do vencimento. Verifica se o valor final inclui multa (2%) e juros (0,03% × 10 dias).

#### `test_consultar_valor` — consultar_valor_atualizado
Chama o método diretamente com uma data 5 dias antes do vencimento e verifica o desconto de 5%.

#### `test_cancelar_boleto` — cancelar_boleto
Cancela um boleto em aberto e verifica se o status mudou para `"cancelado"`.

#### `test_cancelar_boleto_pago` — cancelar_boleto com erro
Tenta cancelar um boleto já pago e verifica se o `ValueError` é lançado corretamente.

---

## Verificação final contra o enunciado

| Requisito da prova | Implementado? |
|---|---|
| Número do boleto gerado automaticamente e único | ✅ `_contador` de classe |
| Nome do pagador | ✅ |
| Valor original com validação positivo | ✅ |
| Data de emissão automática | ✅ `date.today()` |
| Data de vencimento superior à emissão | ✅ validação no construtor e setter |
| Data de pagamento inicialmente None | ✅ |
| Status inicialmente "em aberto" | ✅ |
| Valor final inicialmente 0.00 | ✅ |
| Status muda para "vencido" automaticamente se venceu | ✅ no getter do `status` |
| Método para registrar pagamento | ✅ `registrar_pagamento` |
| Desconto 5% até 3 dias antes | ✅ |
| Multa 2% + juros 0,03%/dia se atrasado | ✅ |
| Método para consultar valor atualizado | ✅ `consultar_valor_atualizado` |
| Método para cancelar (bloqueio se pago) | ✅ `cancelar_boleto` |
| Encapsulamento com atributos privados | ✅ prefixo `_` |
| Decoradores `@property` e `@setter` | ✅ |
| Boleto pago não pode ser pago novamente | ✅ |
| Data de pagamento não pode ser anterior à emissão | ✅ |
| Pytest com teste para cada método + construtor | ✅ 8 testes |
| Simular pagamento antecipado, pontual e atrasado | ✅ 3 testes separados |

> **Observação:** A prova pede *mínimo de uma função de teste para cada método implementado incluindo o construtor*. Temos: 2 para o construtor, 3 para `registrar_pagamento`, 1 para `consultar_valor_atualizado` e 2 para `cancelar_boleto` — todos cobertos.
