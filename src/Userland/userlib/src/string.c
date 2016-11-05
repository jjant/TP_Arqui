#include <string.h>

static void putc_asm(int *);

void putc(int c) {
	putc_asm(&c);
}

void puts(char * str) {
	while(*str)
		putc(*str++);
}

//returns 0 if both strings are equal, 1 if not (need to implement check for str1<str2 and >).
int strcmp(char * str1, char * str2) {
	while(*str1 && *str2) {
		if(*str1 != *str2){
			return 1;
		}
		str1++, str2++;
	}
	return (*str1 || *str2);
}

void break_line() {
	putc('\n');
}