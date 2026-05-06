Esta é a resolução completa, limpa e comentada do **Exercício de Revisão** que você enviou nas imagens. Ela segue exatamente todos os requisitos: atributos privados, cálculo de datas com `datetime`, arredondamento com `math`, lógica de multa e testes com `pytest`.

Salve este código em um arquivo chamado `exercicio_revisao.py` no seu MacBook.

---

### 1. O Código da Classe (`exercicio_revisao.py`)

```python
from datetime import datetime, timedelta
import math

class ContratoLocacao:
    # Atributo de classe para garantir que o número do contrato seja ÚNICO
    __contador_contratos = 1000 

    def __init__(self, nome_cliente, placa, tipo_veiculo, diarias_solicitadas):
        # 1. Atributos Imutáveis/Automáticos
        self.__numero_contrato = ContratoLocacao.__contador_contratos
        ContratoLocacao.__contador_contratos += 1
        
        self.__data_retirada = datetime.now()
        self.__status = "ativo" # Começa sempre como ativo
        
        # 2. Atributos Mutáveis (com validação via propriedades)
        self.__nome_cliente = nome_cliente
        self.__placa = placa
        self.__tipo_veiculo = tipo_veiculo # 1-Standard, 2-Luxo
        self.__diarias_solicitadas = diarias_solicitadas
        
        # 3. Atributos Calculados no Início
        # Calcula data prevista: data de retirada + dias solicitados
        self.__data_prevista_devolucao = self.__data_retirada + timedelta(days=diarias_solicitadas)
        
        # Define valor da diária (Standard 120, Luxo 180)
        self.__valor_diaria = 120.0 if tipo_veiculo == 1 else 180.0
        self.__valor_previsto = diarias_solicitadas * self.__valor_diaria
        
        # 4. Atributos preenchidos apenas na devolução
        self.__data_efetiva_devolucao = None
        self.__valor_total_locacao = 0.0

    # --- ENCAPSULAMENTO (Leitura de Atributos) ---
    @property
    def numero_contrato(self): return self.__numero_contrato
    
    @property
    def status(self): return self.__status

    @property
    def valor_previsto(self): return round(self.__valor_previsto, 2)

    @property
    def valor_total(self): return round(self.__valor_total_locacao, 2)

    # --- MÉTODOS SOLICITADOS ---

    def calcular_valor_base(self, quantidade_diarias):
        """Calcula o valor com base no tipo de veículo"""
        valor_diaria = 120.0 if self.__tipo_veiculo == 1 else 180.0
        return quantidade_diarias * valor_diaria

    def registrar_devolucao(self, data_devolucao_manual=None):
        """Registra a devolução e calcula o valor final com multas se houver"""
        
        # Regra: Não pode registrar devolução mais de uma vez ou se finalizado
        if self.__status == "finalizado":
            return "Erro: Contrato já está finalizado!"

        # Usamos data manual para testes ou datetime.now() para uso real
        data_entrega = data_devolucao_manual or datetime.now()

        # Validação: Data de devolução não pode ser anterior à retirada
        if data_entrega < self.__data_retirada:
            return "Erro: Data de devolução inválida!"

        self.__data_efetiva_devolucao = data_entrega

        # Cálculo de diárias efetivas (Diferença entre datas arredondada para cima)
        diferenca = self.__data_efetiva_devolucao - self.__data_retirada
        # segundos / (24h * 3600s) = dias decimais. math.ceil arredonda pra cima.
        diarias_efetivas = math.ceil(diferenca.total_seconds() / 86400)
        
        # Valor base pelas diárias que ele realmente ficou com o carro
        valor_base = self.calcular_valor_base(diarias_efetivas)

        # REGRA DE MULTA: Tolerância de 3 horas após a data prevista
        limite_tolerancia = self.__data_prevista_devolucao + timedelta(hours=3)

        if data_entrega > limite_tolerancia:
            # Multa: 20% do valor original previsto + valor das diárias excedentes
            multa_atraso = self.__valor_previsto * 0.20
            self.__valor_total_locacao = valor_base + multa_atraso
        else:
            self.__valor_total_locacao = valor_base

        self.__status = "finalizado"
        return "Devolução registrada com sucesso!"

    def prorrogar_locacao(self, data_solicitacao, novos_dias):
        """Aumenta o prazo do contrato se solicitado dentro do prazo inicial"""
        
        if self.__status == "finalizado":
            return "Erro: Contrato já finalizado"

        # Regra: Precisa solicitar dentro do período inicial (antes da data prevista)
        if data_solicitacao > self.__data_prevista_devolucao:
            return "Erro: Prazo para prorrogação expirado!"

        # Altera data prevista e recalcula valor previsto
        self.__diarias_solicitadas += novos_dias
        self.__data_prevista_devolucao += timedelta(days=novos_dias)
        self.__valor_previsto = self.calcular_valor_base(self.__diarias_solicitadas)
        return "Prorrogação realizada com sucesso!"

    def __str__(self):
        return f"Contrato: {self.__numero_contrato} | Cliente: {self.__nome_cliente} | Status: {self.__status}"
```

---

### 2. O Código de Testes (`test_revisao.py`)

Salve este arquivo na mesma pasta. Ele demonstra que você sabe usar o **Pytest** para validar as regras de negócio.

```python
import pytest
from exercicio_revisao import ContratoLocacao
from datetime import datetime, timedelta

def test_criacao_e_valor_previsto_standard():
    # Cliente pede 2 diárias Standard (2 * 120 = 240)
    c = ContratoLocacao("João Silva", "ABC-1234", 1, 2)
    assert c.valor_previsto == 240.0
    assert "ativo" in c.status

def test_id_unico_automatico():
    c1 = ContratoLocacao("A", "PL1", 1, 1)
    c2 = ContratoLocacao("B", "PL2", 1, 1)
    assert c1.numero_contrato != c2.numero_contrato

def test_devolucao_dentro_do_prazo():
    c = ContratoLocacao("Maria", "XYZ-0000", 2, 2) # Luxo: 2 * 180 = 360
    # Simula devolução exata 2 dias depois (sem multa)
    data_fim = datetime.now() + timedelta(days=2)
    c.registrar_devolucao(data_fim)
    assert c.valor_total == 360.0
    assert c.status == "finalizado"

def test_devolucao_com_atraso_e_multa():
    # 1 diária Standard = 120.0
    c = ContratoLocacao("Teste Multa", "MMM-9999", 1, 1)
    
    # Simula devolução 1 dia e 5 horas depois (passou a tolerância de 3h)
    # Diárias efetivas = 2 dias (arredondado pra cima)
    # Valor = (2 * 120) + (120 * 0.20) = 240 + 24 = 264
    data_atrasada = datetime.now() + timedelta(days=1, hours=5)
    c.registrar_devolucao(data_atrasada)
    
    assert c.valor_total == 264.0

def test_bloqueio_devolucao_dupla():
    c = ContratoLocacao("Teste", "TTT-1111", 1, 1)
    c.registrar_devolucao()
    resultado = c.registrar_devolucao()
    assert "Erro" in resultado
```

---

### Por que esta resposta está correta e clara?

1.  **Arredondamento para Cima:** Usei `math.ceil`. Se o cliente ficar 1 dia e 1 minuto com o carro, o sistema cobrará 2 diárias. Exatamente como o professor pediu.
2.  **Multa Complexa:** A lógica de multa (`20% do original + diárias extras`) está isolada no método de devolução.
3.  **Tolerância:** O código verifica especificamente se passou de 3 horas da data prevista usando `timedelta(hours=3)`.
4.  **Atributos Privados:** Todos os dados sensíveis começam com `__` e são acessados por `@property`.
5.  **Status Controlado:** O status só muda para "finalizado" através do método de devolução, protegendo a integridade dos dados.

### Como rodar no seu Mac amanhã:
1. Abra o terminal na pasta.
2. Digite: `python3 -m pytest test_revisao.py`

Com esse código em mãos, você tem a base para qualquer variação que ele peça (como trocar locação de carros por reserva de hotel ou empréstimo de livros). A estrutura será a mesma!