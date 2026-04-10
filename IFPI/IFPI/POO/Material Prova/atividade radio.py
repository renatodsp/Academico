class RadioFM:
    def __init__(self, vol_max, estacoes):
        # os dois tracinhos escondem a variavel pra ninguem mexer 
        self.__volume_min = 0 
        self.__volume_max = vol_max 
        self.__freq_min = 88 
        self.__freq_max = 108 
        self.__estacoes = estacoes 
        
        # estados iniciais
        self.__volume = None
        self.__ligado = False
        self.__estacao_atual = None
        self.__frequencia_atual = None
        self.__antena_habilitada = False

    def set_antena(self, estado):
        self.__antena_habilitada = estado

    def get_status(self):
        return f"on: {self.__ligado} vol: {self.__volume} radio: {self.__estacao_atual}"

    def ligar(self):
        # liga e bota no volume zero 
        self.__ligado = True
        self.__volume = self.__volume_min
        
        # se a antena ta on pega a primeira radio da lista
        if self.__antena_habilitada:
            frequencias = list(self.__estacoes.keys())
            if frequencias:
                self.__frequencia_atual = frequencias[0]
                self.__estacao_atual = self.__estacoes[self.__frequencia_atual]

    def desligar(self):
        # desliga e limpa tudo pra none 
        self.__ligado = False
        self.__volume = None
        self.__frequencia_atual = None
        self.__estacao_atual = None

    def aumentar_volume(self, valor=None):
        if self.__ligado:
            # se nao passar numero aumenta 1 senao usa o valor
            if valor is None:
                novo_volume = self.__volume + 1
            else:
                novo_volume = valor
            
            # trava pra nao passar do maximo
            if novo_volume <= self.__volume_max:
                self.__volume = novo_volume
            else:
                self.__volume = self.__volume_max

    def diminuir_volume(self, valor=None):
        if self.__ligado:
            # se nao passar nada diminui 1 senao usa o valor
            if valor is None:
                novo_volume = self.__volume - 1
            else:
                novo_volume = valor
            
            # trava pra nao ficar menor que zero
            if novo_volume >= self.__volume_min:
                self.__volume = novo_volume
            else:
                self.__volume = self.__volume_min

    def mudar_frequencia(self, frequencia=0):
        if not self.__ligado:
            return

        if frequencia != 0:
            # muda pra frequencia que eu digitei
            self.__frequencia_atual = frequencia
            if frequencia in self.__estacoes:
                # se a radio existe pega o nome 
                self.__estacao_atual = self.__estacoes[frequencia]
            else:
                # se nao tiver avisa que nao existe
                self.__estacao_atual = 'estação inexistente'
        else:
            # se nao digitar nada pula pra proxima radio 
            frequencias = list(self.__estacoes.keys())
            if self.__frequencia_atual in frequencias:
                indice = frequencias.index(self.__frequencia_atual)
                # se tiver na ultima volta pra primeira 
                if indice == len(frequencias) - 1:
                    proxima_freq = frequencias[0]
                else:
                    proxima_freq = frequencias[indice + 1]
            else:
                proxima_freq = frequencias[0]
            
            self.__frequencia_atual = proxima_freq
            self.__estacao_atual = self.__estacoes[proxima_freq]

# --- TESTANDO COM 3 OBJETOS ---

lista = {89.5: 'Cocais', 91.5: 'Mix', 94.1: 'Boa', 99.1: 'Clube'}

r1 = RadioFM(50, lista)
r1.set_antena(True)
r1.ligar()
print(f"Radio 1: {r1.get_status()}")

r2 = RadioFM(30, lista)
r2.ligar()
r2.mudar_frequencia(94.1)
r2.aumentar_volume(10)
print(f"Radio 2: {r2.get_status()}")

r3 = RadioFM(20, lista)
r3.ligar()
r3.mudar_frequencia() # pula pra proxima radio
r3.desligar()
print(f"Radio 3: {r3.get_status()}")