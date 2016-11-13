#ifndef __VIDEO_H__
#define __VIDEO_H__

#include <stdint.h>

static void private_line_paint();
void __clear_screen();
void __puts(const char *);
void __clear_line(int);
void __putc(int);
void __private_line(char *);
void __new_line();
uint8_t __set_color(uint8_t);
void __print_hex(uint64_t);
void __print_base(uint64_t value, uint32_t base);

#endif
