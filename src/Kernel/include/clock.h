#ifndef __CLOCK__H
#define __CLOCK__H

#include <string.h>

int __system_seconds_asm();
int __system_minutes_asm();
int __system_hours_asm();
int __system_seconds();
int __system_minutes();
int __system_hours();
char * __system_time(char *);

#endif