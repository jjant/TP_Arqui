#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <stdint.h>

void __clear_screen();
void __puts(const char *);
void __clear_line(int);
void __putc(char);
void __new_line();

#endif
