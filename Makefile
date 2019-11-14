all : ./bin/gb-asm

CFLAGS = -Wall -g3
CC = cc

./bin/gb-asm : ./gb-asm/main.c
	$(CC) ./gb-asm/main.c -o ./bin/gb-asm $(CFLAGS)
