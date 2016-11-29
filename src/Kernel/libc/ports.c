#include <ports.h>
#include <stdint.h>

void __outportb_asm(uint16_t, uint8_t);
void __outportw_asm(uint16_t, uint16_t);
void __outportdw_asm(uint16_t, uint32_t);
uint8_t __inportb_asm(uint16_t);
uint16_t __inportw_asm(uint16_t);
uint32_t __inportdw_asm(uint16_t);

void __outportb(uint16_t port, uint8_t byte) {
  return __outportb_asm(port, byte);
}

void __outportw(uint16_t port, uint16_t byte) {
  return __outportw_asm(port, byte);
}

void __outportdw(uint16_t port, uint32_t data) {
  return __outportdw_asm(port, data);
}

uint8_t __inportb(uint16_t port) {
  return __inportb_asm(port);
}

uint16_t __inportw(uint16_t port) {
  return __inportw_asm(port);
}

uint32_t __inportdw(uint16_t port) {
  return __inportdw_asm(port);
}

