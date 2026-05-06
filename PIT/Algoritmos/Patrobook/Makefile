CC = gcc
CFLAGS = -Wall -Wextra -O2 -fPIC -shared

# Nome do arquivo final gerado
# Mude para .dll se estiver no Windows, ou deixe .so se for Linux/Mac
TARGET = libpatrobook.so

# Arquivos fonte
SRC = core/patrobook.c

all:
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)
	@echo "Compilação concluída! Biblioteca $(TARGET) gerada com sucesso."

clean:
	rm -f $(TARGET)
	@echo "Biblioteca removida."