.PHONY: hi clean

hi: hello

clean_hi:
	rm -rf build/

hello: hello.o
	ld build/hello.o -o build/hello
	rm -f build/hello.o

hello.o: hello.asm
	@mkdir -p build/
	fasm hello.asm build/hello.o
