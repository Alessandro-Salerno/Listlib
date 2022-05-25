CC = gcc
CFLAGS = -Wextra -Wall -O3
SRC = src/listlib.c
OBJS = tmp/listlib.o
BIN = bin/listlib.a

$(OBJS): $(SRC)
	$(CC) $(CFLAGS) -c $^ -o $@


listlib: $(OBJS) link

link:
	ar rcs $(BIN) $(OBJS)

setup:
	@ mkdir bin
	@ mkdir tmp
