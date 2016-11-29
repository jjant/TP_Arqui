#include <string.h>
#include <stdarg.h>
#include <memory.h>
#include <video.h>

/* Maybe these should go in userland section, as they don't system memory/stuff.
** I don't know.
*/
void printf(char * str, ...) {
  int i = 0;
  char * string_value;

  va_list args;
  va_start(args, str);

  while (str[i] != '\0') {
    char next_char = str[i + 1];
    
    if (is_char(str[i])) __putc(str[i]);
    else if (str[i] == '\\') __putc(next_char == 'n' ? '\n' : '\\'); 
    else if (str[i] == '%') {
      if (next_char != 'c' && next_char != 'd' && next_char != 's') {
        __putc(str[i++]);
        continue;
      }

      switch (next_char) {
      case 'd': putint(va_arg(args, int)); break;
      case 'c': __putc(va_arg(args, int)); break;
      case 's':
        string_value = va_arg(args, char *);
        for (int j = 0; string_value[j] != '\0'; j++) {
          __putc(string_value[j]);
        }
        break;
      }
      i++;
    }
    i++;
  }

  va_end(args);
}

void putint(int value) {
  void * aux = __malloc(30);
  char * str = (char *) aux;
  itoa(value, str);
  __puts(str);
}

uint8_t is_char(char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == ' ' || (c >= 0 && c <= 9);
}

void itoa(int n, char * s) {
  int i, sign = n;
  i = 0;
  char buf[100];
  strcpy(buf, s);

  if (sign < 0) n = -n;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) s[i++] = '-';
  s[i] = '\0';

  str_reverse(s, buf);
}


char * strncpy(char * dest, char * src, int size){
	int i = 0;
	char * ret = dest;
	while(*src && i < size){
		*(dest++) = *(src++);
		i++;
	}
	*dest = '\0';
	return ret;
}

char * strcpy(char * dest, const char * src) {
	dest[0] = '\0';
	strcat(dest, src);
	return dest;	
}

/* Appends str2 to str1.
** str1 must have enough space to accomodate 
** strlen(str1) + strlen(str2) + 1 characters.
*/
char * strcat(char * str1, const char * str2) {
	char * str = str1;
	for(; *str1 != 0; str1++);
	for(; *str2 != 0; *str1++ = *str2++);
	*str1 = '\0';
	return str;
}

int strlen(const char * str) {
	const char * s;
	for(s = str; *s; s++);

	return s - str;
}

/*	Stores a reversed version of source in dest.
**	If dest doesn't have enough space to accomodate strlen(src) + 1
**  character, the behaviour is undefined.
**
**	Returns dest.
*/
char * str_reverse(char * dest, const char * src) {
	char * ret = dest;
	int len = strlen(src);
	
	while(len != 0) {
		*dest = src[len--];
	}

	for(; len != 0; len--, dest++)
		*dest = src[len];
	*dest = '\0';

	return ret;
}

/* Returns zero if str doesn't contain 
** a c character, nonzero otherwise.
*/
int strchr(char * str, char c){
	while(*str){
		if(*str++ == c)
			return 1;
	}
	return 0;
}

/* Convers an int into an string. 
** Buffer must have enough space to accomodate value.
*/

char * int_to_str(int value, char * buffer) {
	char * p = buffer;
	int power = 0;
	int shifter = value;

	do {
		p++;
		shifter /= 10;
	} while(shifter);

	*p = '\0';

	do {
		int dig = value % 10;
		p--;
		*p = dig + '0';
		value /= pow(10, power);
		power++;
	} while(value != 0);

	return buffer;
}
