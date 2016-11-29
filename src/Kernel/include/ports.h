#ifndef __PORTS_H
#define __PORTS_H
#include <stdint.h>

void __outportb(uint16_t, uint8_t);
void __outportw(uint16_t, uint16_t);
void __outportdw(uint16_t, uint32_t);
void __outport64(uint16_t, uint64_t);
uint8_t  __inportb(uint16_t);
uint16_t __inportw(uint16_t);
uint32_t __inportdw(uint16_t);

#endif
