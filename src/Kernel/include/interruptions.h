#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void __sti();

void irq0Handler();
void irq1Handler();
void irq11Handler();

void __IDT_add_handler(int index, uint64_t handler);
void __initialize_IDT();

void setPIC();
void __set_pic_master_asm(uint16_t);
void __set_pic_slave_asm(uint16_t);

#endif
