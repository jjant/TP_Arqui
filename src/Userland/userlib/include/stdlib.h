#ifndef __stdlib_h
#define __stdlib_h
#include <stdint.h>

#ifndef NULL
#define NULL 0
#endif

int atoi(char *str);

void * myalloc(uint64_t size);

char* convertDay(int i);

char* convertMonth(int i);
#endif
