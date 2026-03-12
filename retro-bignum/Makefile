CFLAGS = -O2

all: test1 collatz

collatz.s: collatz.c dec.c bin.c types.h
	: ; - gcc6809 -S -o $@ -O1 -std=gnu99 -fwhole-program -fomit-frame-pointer -ffixed-y collatz.c

clean:
	rm -f test1 collatz
