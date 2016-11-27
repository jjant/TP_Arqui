#ifndef __string_h
#define __string_h

int strcmp(char * s1, char * s2);
int starts_with(char * s, char * start);
int strlen(char * s);
char * strcpy ( char * destination, char * source );
char * strncpy ( char * destination, char * source, int size);
int strchr(char * str, char c);
int strncmp(char * s, char * t, unsigned int n);


#endif

#define __ignore_code
#ifndef __ignore_code

#ifndef __STRING__H
#define __STRING__H

#include <int.h>
#include <stdint.h>

char * strcpy(char *, const char *);
char * strcat(char *, const char *);
int strlen(const char *);
char * str_reverse(char *, const char *);
char * int_to_str(int, char *);
uint8_t is_char(char);
void printf(char *, ...);

#endif

#endif
