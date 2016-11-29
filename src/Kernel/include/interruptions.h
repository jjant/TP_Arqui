#ifndef __INTERRUPTIONS_H
#define __INTERRUPTIONS_H

#include <stdint.h>

void __sti();

void __IDT_add_handler(int, uint64_t);
void __initialize_IDT();

void __set_pic_master_asm(uint16_t);
void __set_pic_slave_asm(uint16_t);

#endif
