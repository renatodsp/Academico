# Instituto Federal do Piaui
# Turma 266 - Técnico em Desenvolvimento de Sistemas
# Alunos:   Renato dos Santos Patrocinio
#           Ruan Batista de Alcântara Rocha

import pytest
from datetime import date, timedelta
from boleto import Boleto


# teste do construtor
def test_criar_boleto():
    vencimento = date.today() + timedelta(days=30)
    boleto = Boleto("Joao", 500.00, vencimento)

    assert boleto.nome_pagador == "Joao"
    assert boleto.valor_original == 500.00
    assert boleto.status == "em aberto"
    assert boleto.data_pagamento is None


# teste do construtor com valor invalido
def test_boleto_valor_invalido():
    with pytest.raises(ValueError):
        Boleto("Ana", -100.00, date.today() + timedelta(days=10))


# teste pagamento antecipado com desconto
def test_pagamento_antecipado():
    vencimento = date.today() + timedelta(days=30)
    boleto = Boleto("Maria", 1000.00, vencimento)

    data_pgto = vencimento - timedelta(days=5)
    boleto.registrar_pagamento(data_pgto)

    assert boleto.status == "pago"
    assert boleto.valor_final == 950.00


# teste pagamento pontual sem desconto
def test_pagamento_pontual():
    vencimento = date.today() + timedelta(days=30)
    boleto = Boleto("Pedro", 1000.00, vencimento)

    boleto.registrar_pagamento(vencimento)

    assert boleto.status == "pago"
    assert boleto.valor_final == 1000.00


# teste pagamento atrasado com multa e juros
def test_pagamento_atrasado():
    vencimento = date.today() + timedelta(days=30)
    boleto = Boleto("Carlos", 1000.00, vencimento)

    data_pgto = vencimento + timedelta(days=10)
    boleto.registrar_pagamento(data_pgto)

    assert boleto.status == "vencido"  # pago apos vencimento fica com status vencido
    assert boleto.valor_final == 1023.00  # 1000 + 20 multa + 3 juros


# teste consultar valor atualizado
def test_consultar_valor():
    vencimento = date.today() + timedelta(days=30)
    boleto = Boleto("Lucas", 1000.00, vencimento)

    valor_com_desconto = boleto.consultar_valor_atualizado(vencimento - timedelta(days=5))
    assert valor_com_desconto == 950.00


# teste cancelar boleto
def test_cancelar_boleto():
    vencimento = date.today() + timedelta(days=30)
    boleto = Boleto("Ana", 200.00, vencimento)

    boleto.cancelar_boleto()
    assert boleto.status == "cancelado"


# teste nao pode cancelar boleto pago
def test_cancelar_boleto_pago():
    vencimento = date.today() + timedelta(days=30)
    boleto = Boleto("Joao", 200.00, vencimento)

    boleto.registrar_pagamento(vencimento)

    with pytest.raises(ValueError):
        boleto.cancelar_boleto()
