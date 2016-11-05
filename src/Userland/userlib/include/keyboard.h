#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <string.h>

int __key_pressed_asm();
void __print_key_pressed();
char __key_pressed();
static char code_to_char(int);

#endif