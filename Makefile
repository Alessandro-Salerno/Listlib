CC = gcc
CFLAGS = -Wextra -Wall -O3
SRC = src/listlib.c
OBJS = tmp/listlib.o
BIN = bin/listlib.a

$(OBJS): $(SRC)
	@ mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $^ -o $@

all: $(OBJS) link

link:
	@ mkdir -p bin
	ar rcs $(BIN) $(OBJS)
