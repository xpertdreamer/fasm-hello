.PHONY: all clean

all: main

clean:
	rm -f main main.o

main: main.o
	ld main.o -o main

main.o: main.asm
	fasm main.asm main.o
