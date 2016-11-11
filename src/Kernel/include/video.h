#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <stdint.h>

void __clear_screen();
void __puts(const char *);
void __clear_line(int);
void __putc(int);
void __new_line();
uint8_t __set_color(uint8_t);

#endif
