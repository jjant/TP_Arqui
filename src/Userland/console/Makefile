include ../Makefile.inc

MODULE=console.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)
SOURCES_LIB=$(wildcard ../userlib/src/*.c)
SOURCES_LIB_ASM=$(wildcard ../userlib/src/asm/*.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)
OBJECTS_LIB=$(SOURCES_LIB:.c=.o)
OBJECTS_LIB_ASM=$(SOURCES_LIB_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS_ASM) $(OBJECTS) $(OBJECTS_LIB_ASM) $(OBJECTS_LIB)
	$(LD) $(LDFLAGS) -T console.ld -o ../$(MODULE) $(OBJECTS) $(OBJECTS_ASM) $(OBJECTS_LIB) $(OBJECTS_LIB_ASM)

%.o: %.c
	$(GCC) $(GCCFLAGS) -I./include -I../userlib/include -c $< -o $@

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean print
