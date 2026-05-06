class Cofre_Eletronico():
    def __init__(self, senha, estado="fechado", tentativas_restantes=3):
        self.senha = senha
        self.estado = estado
        self.tentativas_restantes = tentativas_restantes

    #verifica se a senha esta correta e muda o estado para aberto, -=1 a cada tentativa errada
    def abrir_cofre(self, senha):
        if self.estado == "aberto":
            return "Aviso: O cofre já está aberto."

        if self.tentativas_restantes <= 0:
            return "Número de tentativas esgotado. Cofre bloqueado."

        if senha == self.senha:
            self.estado = "aberto"
            self.tentativas_restantes = 3
            return "Cofre aberto com sucesso!"
        else:
            self.tentativas_restantes -= 1
            if self.tentativas_restantes <= 0:
                return "Número de tentativas esgotado. Cofre bloqueado."
            return f"Senha incorreta. Tentativas restantes: {self.tentativas_restantes}"


    def fechar_cofre(self):
        if self.estado == "fechado":
            return "Aviso: O cofre já está fechado."
        else:
            self.estado = "fechado"
            return "Cofre fechado."


    def resetar_tentativas(self):
        if self.estado == "aberto":
            self.tentativas_restantes = 3
            return "Tentativas resetadas para 3."
        else:
            return "Não é possível resetar as tentativas enquanto o cofre estiver fechado."


    def trocar_senha(self, senha_antiga, nova_senha):
        if self.estado == "aberto":
            if senha_antiga == self.senha:
                self.senha = nova_senha
                print("Sucesso: Senha alterada com sucesso.")
            else:
                print("Erro: Senha antiga incorreta.")
        else:
            print("Erro: O cofre precisa estar aberto para trocar a senha.")

    def exibir_estado(self):
        print(f"Estado Atual -> Status: {self.estado.capitalize()} | Tentativas Restantes: {self.tentativas_restantes}")