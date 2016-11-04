#include <string.h>

static void putc_asm(int *);

void putc(int c) {
	putc_asm(&c);
}

void puts(char * str) {
	while(*str)
		putc(*str++);
}