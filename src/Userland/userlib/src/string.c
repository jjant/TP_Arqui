#include <stdint.h>
#include <stdarg.h>
#include <memory.h>
#include <string.h>
#include <number.h>


static void putc_asm(int *);

void putc(int c) {
	putc_asm(&c);
}

void puts(char * str) {
	while(*str)
		putc(*str++);
}

void putint(int value) {
  void * aux = malloc(MAX_INT_LENGTH);
  char * str = (char *) aux;
  itoa(value, str);
  puts(str);
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

uint8_t is_char(char c) {
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == ' ';
}

uint8_t is_digit(char c) {
  return c >= '0' && c <= '9';
}


void printf(char * str, ...) {
  int i = 0;
  char * string_value;

  va_list args;
  va_start(args, str);

  while (str[i] != '\0') {
    char next_char = str[i + 1];
    if (is_char(str[i])) putc(str[i]);
    else if (str[i] == '\\') putc(next_char == 'n' ? '\n' : '\\'); 
    else if (str[i] == '%') {
      if (next_char != 'c' && next_char != 'd' && next_char != 's') {
        putc(str[i++]);
        continue;
      }

      switch (next_char) {
      case 'd': putint(va_arg(args, int)); break;
      case 'c': putc(va_arg(args, int)); break;
      case 's':
        string_value = va_arg(args, char *);
        for (int j = 0; string_value[j] != '\0'; j++) {
          putc(string_value[j]);
        }
        break;
      }
      i++;
    }
    i++;
  }

  va_end(args);
}