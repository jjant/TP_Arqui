#ifndef STRING_H
#define STRING_H

void reverse(char *);
int strcmp(const char *, const char *);
int starts_with(char * s, char * start);
int strlen(char * s);
char * strcpy ( char * destination, char * source );
char * strncpy ( char * destination, char * source, int size);
int strchr(char * str, char c);
int strncmp(char * s, char * t, unsigned int n);
void putc(int);
void puts(char *);
int strlen(char *);
void printf(char *, ...);
int atoi(const char *;);
int isdigit(char);

#endif
