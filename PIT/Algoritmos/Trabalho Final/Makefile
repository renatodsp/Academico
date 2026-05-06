# Makefile - Patrobook
# Trabalho Final - Algoritmos e Estruturas de Dados (PIT)

CC = gcc
CFLAGS = -Wall -Wextra -O2 -std=c99
TARGET = patrobook
SRCS = main.c usuario.c rede.c persistencia.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe patrobook.dat

run: $(TARGET)
	./$(TARGET)

.PHONY: all clean run
