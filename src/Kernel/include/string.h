#ifndef __STRING__H
#define __STRING__H

#include <int.h>

char * strcpy(char *, const char *);
char * strcat(char *, const char *);
int strlen(const char *);
char * str_reverse(char *, const char *);
char * int_to_str(int, char *);
uint8_t is_char(char);
void printf(char *, ...);

#endif