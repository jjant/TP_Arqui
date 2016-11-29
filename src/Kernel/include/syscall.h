#ifndef __SYSCALL_H
#define __SYSCALL_H

typedef unsigned long size_t;

void __syscall_handler();
void __initialize_syscall_vector();
void __write(char *, size_t);
char __keyboard_key();

#endif
