CC = gcc
CFLAGS = -Wall -Wextra -std=c11
TARGET = esi_escape
SRCS = main.c motor.c utilidades.c usuarios.c ficheros.c
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
