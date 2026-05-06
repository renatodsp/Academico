# Instituto Federal do Piaui
# Turma 266 - Técnico em Desenvolvimento de Sistemas
# Alunos:   Renato dos Santos Patrocinio
#           Ruan Batista de Alcântara Rocha            

from datetime import date


class Boleto:
    # contador pra gerar numero unico
    _contador = 0

    def __init__(self, nome_pagador, valor_original, data_vencimento):
        # validacao do nome
        if not nome_pagador or not nome_pagador.strip():
            raise ValueError("nome do pagador nao pode ser vazio")

        # validacao do valor
        if valor_original <= 0:
            raise ValueError("valor original deve ser positivo")

        # data de emissao e a data atual
        self._data_emissao = date.today()

        # validacao da data de vencimento tem que ser depois da emissao
        if data_vencimento <= self._data_emissao:
            raise ValueError("data de vencimento deve ser posterior a data de emissao")

        # gera numero unico automaticamente
        Boleto._contador += 1
        self._numero = Boleto._contador

        # atributos imutaveis
        self._nome_pagador = nome_pagador
        self._valor_original = valor_original

        # atributos mutaveis
        self._data_vencimento = data_vencimento
        self._data_pagamento = None
        self._status = "em aberto"
        self._valor_final = 0.00

    # propriedades de leitura pra atributos imutaveis

    @property
    def numero(self):
        return self._numero

    @property
    def nome_pagador(self):
        return self._nome_pagador

    @property
    def valor_original(self):
        return self._valor_original

    @property
    def data_emissao(self):
        return self._data_emissao

    # propriedades de leitura e escrita pra atributos mutaveis

    @property
    def data_vencimento(self):
        return self._data_vencimento

    @data_vencimento.setter
    def data_vencimento(self, nova_data):
        if nova_data <= self._data_emissao:
            raise ValueError("data de vencimento deve ser posterior a data de emissao")
        if self._status == "pago":
            raise ValueError("nao pode alterar vencimento de boleto pago")
        self._data_vencimento = nova_data

    @property
    def data_pagamento(self):
        return self._data_pagamento

    @property
    def status(self):
        # se ta em aberto e ja passou do vencimento muda pra vencido
        if self._status == "em aberto" and date.today() > self._data_vencimento:
            self._status = "vencido"
        return self._status

    @property
    def valor_final(self):
        return self._valor_final

    def consultar_valor_atualizado(self, data_referencia=None):
        # consulta o valor considerando desconto ou juros
        if data_referencia is None:
            data_referencia = date.today()

        dias_ate_vencimento = (self._data_vencimento - data_referencia).days

        if dias_ate_vencimento >= 3:
            # desconto de 5% se pago ate 3 dias antes do vencimento
            valor = self._valor_original * 0.95
        elif dias_ate_vencimento >= 0:
            # pagamento no prazo sem desconto
            valor = self._valor_original
        else:
            # atrasado entao cobra multa de 2% e juros de 0.03% por dia
            dias_atraso = abs(dias_ate_vencimento)
            multa = self._valor_original * 0.02
            juros = self._valor_original * 0.0003 * dias_atraso
            valor = self._valor_original + multa + juros

        return round(valor, 2)

    def registrar_pagamento(self, data_pagamento=None):
        # registra o pagamento do boleto
        if data_pagamento is None:
            data_pagamento = date.today()

        if self._status == "pago":
            raise ValueError("boleto ja foi pago")
        if self._status == "cancelado":
            raise ValueError("boleto cancelado nao pode ser pago")
        if data_pagamento < self._data_emissao:
            raise ValueError("data de pagamento nao pode ser anterior a emissao")

        self._data_pagamento = data_pagamento
        self._valor_final = self.consultar_valor_atualizado(data_pagamento)

        # status muda conforme a data de pagamento
        if data_pagamento > self._data_vencimento:
            self._status = "vencido"
        else:
            self._status = "pago"

    def cancelar_boleto(self):
        # cancela o boleto se nao tiver sido pago
        if self._status == "pago":
            raise ValueError("nao pode cancelar boleto que ja foi pago")
        self._status = "cancelado"

    def __str__(self):
        return (
            f"Boleto {self._numero} | Pagador: {self._nome_pagador} | "
            f"Valor: R${self._valor_original:.2f} | Status: {self.status} | "
            f"Vencimento: {self._data_vencimento} | Valor Final: R${self._valor_final:.2f}"
        )
