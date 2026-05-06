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
    vencimento = date.today()