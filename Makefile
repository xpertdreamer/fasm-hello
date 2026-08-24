.PHONY: hi clean all run

all: fasm-test

fasm-test: main.c extern.asm
	@mkdir -p build/
	fasm extern.asm build/extern.o
	gcc -Wall -Wextra -isystem thirdparty main.c build/extern.o -o build/fasm-test -lraylib -lm
	./build/fasm-test

hi: hello

clean:
	rm -rf build/

hello: hello.o
	ld build/hello.o -o build/hello
	rm -f build/hello.o

hello.o: hello.asm
	@mkdir -p build/
	fasm hello.asm build/hello.o
