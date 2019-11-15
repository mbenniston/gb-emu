all : ./bin/gb-asm ./bin/gb-emu

CFLAGS = -Wall -g3
CC = cc

./bin/gb-emu : ./src/main.c ./src/cpu.c ./src/memory.c ./src/instructions.c
	$(CC) ./src/main.c ./src/cpu.c ./src/memory.c ./src/instructions.c -o ./bin/gb-emu $(CFLAGS) -lcfx -lX11 -lm

./bin/gb-asm : ./gb-asm/main.c
	$(CC) ./gb-asm/main.c -o ./bin/gb-asm $(CFLAGS)
