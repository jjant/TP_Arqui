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
char __pop_key();
static char code_to_char(int);

#endif