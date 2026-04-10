class Projetil:
    def __init__(self, posicao, direcao, velocidade, aceleracao, dano, vida_max):
        self.posicao = posicao          # Ex: [x, y]
        self.direcao = direcao          # Ex: [dx, dy] - indica pra onde o projetil vai. x = cosseno, y = seno da direção
        self.velocidade = velocidade    #Velocidade do movimento
        self.aceleracao = aceleracao    #Aceleração p/seg com velocidade inicial e aumentando com o tempo (v = v0 + a*t)
        self.dano_base = dano           #Dano que o projétil causará ao atingir um alvo
        self.tempo_de_vida = vida_max   # Segundos
        self.ativo = True               # Evento para indicar se o projétil existe ou já foi destruído

    def atualizar_posicao(self, delta_time): 
        #"""Atualiza a física do projétil a cada frame.""" # delta_time é o tempo em segundos desde a última atualização (ex: 0.016 para 60 FPS)
                                                          # delta_time = tempo_atual - tempo_anterior
        if self.ativo == False:                           # delta_time = 1/fps (60 FPS -> 1/60 = 0.016s)
            return

        #(velocidade += aceleração * tempo)
        self.velocidade += self.aceleracao * delta_time
        
        #atualização da posição: (posição += direção * velocidade * tempo)
        self.posicao[0] += self.direcao[0] * self.velocidade * delta_time
        self.posicao[1] += self.direcao[1] * self.velocidade * delta_time

        #reduz o tempo de vida do projétil a cada frame
        self.tempo_de_vida -= delta_time
        if self.tempo_de_vida <= 0:
            self.dissipar()

    def ao_colidir(self, alvo):
        #"""Lógica de impacto."""
        print(f"Impacto! Causando {self.dano_base} de dano em {alvo}.")
        self.dissipar()

    def dissipar(self):
        #"""Prepara o objeto para ser limpo da memória."""
        self.ativo = False
        print("Projétil destruído e removido do processamento.")


#apresentar usando pygame, demonstrando o movimento do projétil.