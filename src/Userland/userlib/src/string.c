#include <string.h>
#include <stdint.h>
#include <stdarg.h>
#include <memory.h>
#include <string.h>
#include <number.h>

int atoi(const char *c) {
    int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' )
    {
        if( *c == '-' ) sign = -1;
        c++;
    }
    while (isdigit(*c))
    {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return (value * sign);
}

int isdigit(char c) {
    if ((c>='0') && (c<='9')) 
      return 1;
    return 0;
}

int strncmp(char * s, char * t, unsigned int n) {
  int i;
  for (i = 0; i < n-1 && s[i] != '\0' && t[i] != '\0' && s[i] == t[i]; i++)
    ;
  return s[i]-t[i];
}

//Devuelve TRUE si start es subcadena inicial de str, FALSE (0) 
//si esto no pasa
int starts_with(char * str, char * start){
  while(*str != 0 && *start != 0){
    if(*(str++) != *(start++)){
      return 0;
    }
  }
  return *start == 0;
}


char * strcpy ( char * destination, char * source){
  return strncpy(destination, source, strlen(source) + 1);
}


char * strncpy ( char * destination, char * source, int size){
  int i = 0;
  char * ret = destination;
  while(*source && i < size){
    *(destination++) = *(source++);
    i++;
  }
  *destination = '\0';
  return ret;
}

int strchr(char*str, char c){
  while(*str){
    if(*str++ == c)
      return 1;
  }
  return 0;
}

void putc(int c) {
  putc_asm(&c);
}

void puts(char * str) {
  while(*str) putc(*str++);
}

uint8_t is_char(char c) {
  return c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == ' ' || c >= 0 && c <= 9;
}

void putint(int value) {
  void * aux = malloc(MAX_INT_LENGTH);
  char * str = (char *) aux;
  itoa(value, str);
  puts(str);
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
