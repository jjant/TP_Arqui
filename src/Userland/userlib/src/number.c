#include <string.h>
#include <number.h>

void itoa(int n, char * s) {
  int i, sign = n;
  i = 0;

  if (sign < 0) n = -n;
  do {
    s[i++] = n % 10 + '0';
  } while ((n /= 10) > 0);

  if (sign < 0) s[i++] = '-';
  s[i] = '\0';

  reverse(s);
}

int atoi(const char *c) {
    int value = 0;
    int sign = 1;
    if( *c == '+' || *c == '-' ) {
        if( *c == '-' ) sign = -1;
        c++;
    }
    while (is_digit(*c)) {
        value *= 10;
        value += (int) (*c-'0');
        c++;
    }
    return (value * sign);
}