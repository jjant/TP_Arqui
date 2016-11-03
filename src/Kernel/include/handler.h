#ifndef __HANDLER_H
#define __HANDLER_H

void sti();
void irq0Handler();
void setPicMaster(uint16_t);
void __tick_handler();

#endif