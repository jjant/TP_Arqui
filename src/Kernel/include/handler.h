#ifndef __HANDLER_H
#define __HANDLER_H

#include <stdint.h>

void sti();
void irq0Handler();
void irq1Handler();
void irq11Handler();
void __set_pic_master(uint8_t);
void __set_slave_master(uint8_t);
void __tick_handler();
void __key_handler();
void __initialize_handlers();

#endif
