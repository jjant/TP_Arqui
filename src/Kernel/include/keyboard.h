#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <video.h>
#include <string.h>

#define BUFFER_SIZE 128

int __key_pressed_asm();
int __getchar();
void __print_key_pressed();
char __key_pressed();
char __push_key();
void __flush();
void __change_keyboard(uint8_t);
char __pop_key();

#endif
