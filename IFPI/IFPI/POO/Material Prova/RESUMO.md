Este é o seu **Guia Mestre de Consulta Offline**. 


Aqui está tudo o que você precisa, organizado por tópicos, com os comandos do Mac e a lógica dos slides e exercícios.

---

### 1. COMANDOS NO MACBOOK (TERMINAL)
Como você está no Mac, use sempre `python3` e o prefixo `-m` para o pytest.

*   **Rodar um script:** `python3 nome_do_arquivo.py`
*   **Rodar testes (Pytest):** `python3 -m pytest nome_do_arquivo_teste.py`
*   **Rodar testes vendo os prints:** `python3 -m pytest -s nome_do_arquivo_teste.py`
*   **Limpar a tela do terminal:** `clear`

---

### 2. DICIONÁRIO TÉCNICO (PARA TEORIA)
*   **Classe:** O molde (ex: Classe `Carro`).
*   **Objeto/Instância:** O que foi criado pelo molde (ex: `meu_carro`).
*   **Atributo:** Variável dentro da classe (característica).
*   **Método:** Função dentro da classe (ação).
*   **Encapsulamento:** Esconder dados com `__` para proteção.
*   **Abstração:** Trazer algo do mundo real para o código (foco no que é importante).

---

### 3. MODELO COMPLETO: CLASSE + ENCAPSULAMENTO + DATETIME
Este modelo resolve o exercício de **Locação de Veículos** que o professor passou.

```python
from datetime import datetime, timedelta
import math

class Locacao:
    # Atributo de Classe (para gerar ID único)
    _contador_id = 1

    def __init__(self, cliente, tipo_veiculo):
        # ATRIBUTOS PRIVADOS (Encapsulamento - Slide 6)
        self.__id = Locacao._contador_id
        Locacao._contador_id += 1
        
        self.__cliente = cliente
        self.__tipo = tipo_veiculo  # 1-Standard, 2-Luxo
        self.__status = "ativo"
        
        # DATETIME (Datas automáticas)
        self.__data_retirada = datetime.now()
        # Previsão de 1 dia (exemplo)
        self.__data_prevista = self.__data_retirada + timedelta(days=1)

    # --- ENCAPSULAMENTO: GETTERS (Leitura) ---
    @property
    def id(self): return self.__id

    @property
    def status(self): return self.__status

    # --- ENCAPSULAMENTO: SETTER (Escrita com Validação - Slide 16) ---
    @property
    def cliente(self): return self.__cliente

    @cliente.setter
    def cliente(self, novo_nome):
        # Exemplo de validação de nome do Slide 16
        if len(novo_nome.split(" ")) >= 2:
            self.__cliente = novo_nome
        else:
            print("Erro: Digite nome e sobrenome!")

    # --- MÉTODOS DE CÁLCULO (Regras de Negócio) ---
    def registrar_devolucao(self, data_manual=None):
        if self.__status == "finalizado":
            return "Erro: Já finalizado"
        
        data_efetiva = data_manual or datetime.now()
        
        # Diferença de datas (PDF Revisão)
        diferenca = data_efetiva - self.__data_retirada
        # math.ceil arredonda para cima (1.1 dias -> 2 dias)
        diarias = math.ceil(diferenca.total_seconds() / 86400)
        
        self.__status = "finalizado"
        return f"Devolução registrada. Diárias: {diarias}"

    def __str__(self):
        return f"Contrato {self.__id} - Cliente: {self.__cliente}"
```

---

### 4. GUIA DE DATETIME (CHEAT SHEET)
```python
from datetime import datetime, timedelta

agora = datetime.now()
# Formatar para BR: 15/05/2023
texto = agora.strftime("%d/%m/%Y %H:%M")

# Criar data manual: ano, mes, dia, hora, minuto
data_antiga = datetime(2023, 10, 20, 14, 30)

# Somar tempo
amanha = agora + timedelta(days=1)
tolerancia = agora + timedelta(hours=3)

# Subtrair datas (gera um timedelta)
atraso = agora - data_antiga
print(atraso.days) # dias de diferença
```

---

### 5. GUIA DE PYTEST (COMANDOS E ESTRUTURA)
Crie um arquivo chamado `test_prova.py`.

**As regras para o Pytest funcionar:**
1. O arquivo deve começar com `test_`.
2. A função deve começar com `test_`.
3. Use o comando `assert` (afirmar).

```python
import pytest
from seu_arquivo import Locacao # Importe sua classe aqui

def test_criacao_contrato():
    obj = Locacao("Joao Silva", 1)
    assert obj.id == 1
    assert obj.status == "ativo"

def test_validacao_nome_curto():
    obj = Locacao("Joao Silva", 1)
    obj.cliente = "Marcos" # Deve falhar na validação do setter
    # O nome deve continuar o antigo pois o novo é curto
    assert obj.cliente == "Joao Silva"

"""
NO TERMINAL DO MAC:
python3 -m pytest test_prova.py
"""
```

---

### DICAS FINAIS PARA A PROVA:

1.  **Encapsulamento (`__` vs `_`):** 
    *   Use `self.__atributo` para ser privado (Slide 6). 
    *   Se tentar acessar `obj.__atributo` de fora, vai dar `AttributeError`. A solução é criar o `@property`.
2.  **O `self`:** Nunca esqueça o `self` nos parênteses dos métodos: `def acao(self):`.
3.  **Furo no Encapsulamento:** Se o professor perguntar o que é (Slide 12), diga que é quando permitimos que atributos internos sejam alterados diretamente sem passar por um método de validação.
4.  **Organização:** Deixe uma pasta aberta com esses arquivos. Se ele pedir uma classe nova, você copia o `__init__`, o `@property` e o `@setter` e apenas troca os nomes.

**Boa sorte! Você tem todo o material necessário agora.** Se o terminal der erro, lembre-se: `python3 -m pytest`.