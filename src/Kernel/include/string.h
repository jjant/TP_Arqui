#ifndef __STRING__H
#define __STRING__H

#include <int.h>
#include <stdint.h>

int strchr(char *, char);
int strncmp(char *, char *, unsigned int);
char * strncpy ( char *, char *, int);
char * strcpy(char *, const char *);
char * strcat(char *, const char *);
int strlen(const char *);
char * str_reverse(char *, const char *);
char * int_to_str(int, char *);
uint8_t is_char(char);
void printf(char *, ...);

#endif
