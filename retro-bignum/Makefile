# $(SHELF) is where everything we use gets installed.
# github.com/strickyak/coco-shelf can be used to build it.
SHELF=$(shell cd ../.. ; pwd)

# for gcc on linux
CFLAGS = -O2

# for gcc6809 on OS9
GCC6809= $(SHELF)/bin/gcc6809
GCC_OPT= -O1
GCC_PRAG= -std=gnu99 -fwhole-program -fomit-frame-pointer -ffixed-y -nostdlib -ffreestanding
LWASM= $(SHELF)/bin/lwasm
LW_PRAG= --pragma=forwardrefmax,undefextern,cescapes,importundefexport,dollarnotlocal,condundefzero --no-warn=ifp1
LW_INCL= -I'$(SHELF)/nitros9/level3/coco3/cmds/' -I'$(SHELF)/nitros9/defs/'

# for gcc6809pic
GCC6809PIC_DIR = $(SHELF)/gcc6809pic/
GCC6809PIC = go run $(GCC6809PIC_DIR)/ --lib1=$(SHELF)/gccretro/gcc/config/m6809/libgcc1.s --rules=$(GCC6809PIC_DIR)/rules.txt

all: test1 collatz collatz.os9

collatz.s: collatz.c dec.c bin.c types.h
	$(GCC6809) -S -o '$@' $(GCC_OPT) $(GCC_PRAG) collatz.c

collatz.s.asm: collatz.s
	$(GCC6809PIC) >'$@' -mem=2048 -name=collatz collatz.s

collatz.os9: collatz.s.asm
	$(LWASM) $(LW_PRAG) $(LW_INCL) -o'$@' --format=os9 collatz.s.asm
	go run ../../borges-saver/ --outdir=/tmp/borges .
	$(SHELF)/bin/os9 copy -r $(SHELF)/collatz/retro-bignum/collatz.os9 $(SHELF)/tfr9/v3/generated/level1.dsk,cmds/collatz
	$(SHELF)/bin/os9 attr -e -pe -r -pr $(SHELF)/tfr9/v3/generated/level1.dsk,cmds/collatz


clean:
	rm -f test1 collatz
	rm -f _* ,* *.log *.map *.list *.s *.s.asm *.os9
