include Makefile.inc

KERNEL=kernel.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard asm/*.asm)
SOURCES_LIBC=$(wildcard libc/*.c)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_LIBC=$(SOURCES_LIBC:.c=.o)
LOADERSRC=loader.asm

LOADEROBJECT=$(LOADERSRC:.asm=.o)
STATICLIBS=

all: libc $(KERNEL)

$(KERNEL): $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_LIBC) $(STATICLIBS) $(OBJECTS_ASM)
	$(LD) $(LDFLAGS) -T kernel.ld -o $(KERNEL) $(LOADEROBJECT) $(OBJECTS) $(OBJECTS_LIBC) $(OBJECTS_ASM) $(STATICLIBS)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

$(LOADEROBJECT):
	$(ASM) $(ASMFLAGS) $(LOADERSRC) -o $(LOADEROBJECT)

clean:
	rm -rf asm/*.o *.o *.bin

.PHONY: all clean
