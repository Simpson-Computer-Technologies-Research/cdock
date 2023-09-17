CC = gcc

ARGS = -Wall -std=c99

all:
	$(CC) $(ARGS) ./src/main.c -o ./build/cdock
