CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-parameter -std=c11
TARGET = esi_escape
SRCS = main.c motor.c usuarios.c ficheros.c auxiliar.c objetos.c sala.c conexiones.c puzzles.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean debug run re

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

debug: CFLAGS += -g
debug: re

clean:
	rm -f $(OBJS) $(TARGET)

re: clean all

run: all
	./$(TARGET)
