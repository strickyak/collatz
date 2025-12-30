all: run

run: check-all-collatz-uint32-using-uint64
	time ./$<

check-all-collatz-uint32-using-uint64: check-all-collatz-uint32-using-uint64.c 
	gcc -O2 $< -o'$@'
