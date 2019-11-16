all : ./bin/gb-asm ./bin/gb-emu ./tests/source.bin

CFLAGS = -Wall -g3
CC = cc

./bin/gb-emu : ./src/main.c ./src/cpu.c ./src/memory.c ./src/instructions.c
	$(CC) ./src/main.c ./src/cpu.c ./src/memory.c ./src/instructions.c -o ./bin/gb-emu $(CFLAGS) -lcfx -lX11 -lm

./tests/source.bin : ./tests/source.s ./bin/gb-asm
	./bin/gb-asm ./tests/source.s ./tests/source.bin

./bin/gb-asm : ./gb-asm/main.c
	$(CC) ./gb-asm/main.c ./src/instructions.c ./src/cpu.c  ./src/memory.c -o ./bin/gb-asm $(CFLAGS)

clean : 
	rm ./bin/*
	rm ./tests/*.bin