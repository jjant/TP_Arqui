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
