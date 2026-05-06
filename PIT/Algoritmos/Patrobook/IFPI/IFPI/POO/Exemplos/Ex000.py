class Celular:
    # O Construtor: define o que o objeto "tem" ao nascer
    def __init__(self, marca, modelo, bateria):
        self.marca = marca      # self é o "nome" do próprio objeto
        self.modelo = modelo
        self.bateria = bateria

# Criando objetos (instâncias)
meu_celular = Celular("Apple", "iPhone 15", 100)
teu_celular = Celular("Samsung", "S24", 95)