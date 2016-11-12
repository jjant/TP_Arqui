#include <string.h>

static void putc_asm(int *);

void putc(int c) {
	putc_asm(&c);
}

void puts(char * str) {
	while(*str)
		putc(*str++);
}

void reverse(char * s) {
  int i, j;
  char c;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
 }

int strlen(char * s) {
    char * start = s;
    while(*s != 0) s++;
    return s - start;
}

//returns 0 if both strings are equal, 1 if not (need to implement check for str1<str2 and >).
int strcmp(const char * str1, const char * str2) {
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