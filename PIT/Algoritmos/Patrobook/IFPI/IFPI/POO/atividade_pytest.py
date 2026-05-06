class Pessoa:
    def __init__(self, nome, idade):
        self.nome = nome
        self.idade = idade

    def fazer_aniversario(self):
        self.idade += 1

    def mudar_nome(self, novo_nome):
        self.nome = novo_nome

    def e_maior_de_idade(self):
        return self.idade >= 18

class TestPessoa:
    def test_construtor(self):
        p = Pessoa("Ana", 20)
        assert p.nome == "Ana"
        assert p.idade == 20

    def test_fazer_aniversario(self):
        p = Pessoa("Carlos", 25)
        p.fazer_aniversario()
        assert p.idade == 26

    def test_mudar_nome(self):
        p = Pessoa("Maria", 30)
        p.mudar_nome("Maria Silva")
        assert p.nome == "Maria Silva"

    def test_e_maior_de_idade(self):
        p1 = Pessoa("João", 17)
        p2 = Pessoa("Pedro", 18)
        assert p1.e_maior_de_idade() == False
        assert p2.e_maior_de_idade() == True
