from datetime import datetime


class Cofre_Eletronico():
    def __init__(self, senha, codigo_mestre, estado="fechado", tentativas_restantes=3):
        self.senha = senha
        self.estado = estado
        self.tentativas_restantes = tentativas_restantes
        self.bloqueado = False  # estado de bloqueio automático
        self.codigo_mestre = codigo_mestre  # código mestre para desbloquear o cofre
        self.historico = []  # histórico de tentativas de abertura

    # registra uma tentativa no histórico com data/hora e resultado
    def __registrar_tentativa(self, sucesso):
        self.historico.append({
            "data_hora": datetime.now().strftime("%d/%m/%Y %H:%M:%S"),
            "sucesso": sucesso
        })

    # exibe o histórico de todas as tentativas de abertura
    def exibir_historico(self):
        if not self.historico:
            print("Nenhuma tentativa registrada.")
            return

        print("=" * 50)
        print("HISTÓRICO DE ACESSOS")
        print("=" * 50)
        for i, tentativa in enumerate(self.historico, 1):
            resultado = "Bem-sucedida" if tentativa["sucesso"] else "Falha"
            print(f"{i}. [{tentativa['data_hora']}] - {resultado}")
        print("=" * 50)

    # verifica se a senha esta correta e muda o estado para aberto, -=1 a cada tentativa errada
    def abrir_cofre(self, senha):
        if self.bloqueado:
            return "Cofre bloqueado! Use o código mestre para desbloquear."

        if self.estado == "aberto":
            return "Aviso: O cofre já está aberto."

        if self.tentativas_restantes <= 0:
            self.bloqueado = True
            return "Número de tentativas esgotado. Cofre bloqueado."

        if senha == self.senha:
            self.estado = "aberto"
            self.tentativas_restantes = 3
            self.__registrar_tentativa(True)
            return "Cofre aberto com sucesso!"
        else:
            self.tentativas_restantes -= 1
            self.__registrar_tentativa(False)
            if self.tentativas_restantes <= 0:
                self.bloqueado = True
                return "Número de tentativas esgotado. Cofre bloqueado automaticamente!"
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

    # desbloqueia o cofre usando o código mestre
    def desbloquear_cofre(self, codigo):
        if not self.bloqueado:
            return "O cofre não está bloqueado."

        if codigo == self.codigo_mestre:
            self.bloqueado = False
            self.tentativas_restantes = 3
            return "Cofre desbloqueado com sucesso! Tentativas restauradas."
        else:
            return "Código mestre incorreto. Cofre permanece bloqueado."

    # troca a senha com validação: mínimo 6 caracteres e pelo menos 1 número
    def trocar_senha(self, senha_antiga, nova_senha):
        if self.estado == "aberto":
            if senha_antiga == self.senha:
                # verifica se a nova senha tem no mínimo 6 caracteres
                if len(nova_senha) < 6:
                    print("Erro: A nova senha deve ter no mínimo 6 caracteres.")
                    return
                # verifica se a nova senha contém pelo menos um número
                if not any(c.isdigit() for c in nova_senha):
                    print("Erro: A nova senha deve conter pelo menos um número.")
                    return
                self.senha = nova_senha
                print("Sucesso: Senha alterada com sucesso.")
            else:
                print("Erro: Senha antiga incorreta.")
        else:
            print("Erro: O cofre precisa estar aberto para trocar a senha.")

    def exibir_estado(self):
        status_bloqueio = " | BLOQUEADO" if self.bloqueado else ""
        print(f"Estado Atual -> Status: {self.estado.capitalize()} | Tentativas Restantes: {self.tentativas_restantes}{status_bloqueio}")
