include ../Makefile.inc

MODULE=0000-sampleCodeModule.bin
SOURCES=$(wildcard *.c)
SOURCES_ASM=$(wildcard *.asm)
OBJECTS=$(SOURCES:.c=.o)
OBJECTS_ASM=$(SOURCES_ASM:.asm=.o)

all: $(MODULE)

$(MODULE): $(OBJECTS_ASM) $(OBJECTS)
	$(LD) $(LDFLAGS) -T sampleCodeModule.ld -o ../$(MODULE) $(OBJECTS) $(OBJECTS_ASM) 

%.o : %.asm
	$(ASM) $(ASMFLAGS) $< -o $@

%.o: %.c
	$(GCC) $(GCCFLAGS) -c $< -o $@

clean:
	rm -rf *.o

.PHONY: all clean print
