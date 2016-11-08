#ifndef __HANDLER_H
#define __HANDLER_H

void sti();
void irq0Handler();
void irq1Handler();
void setPicMaster(uint16_t);
void __tick_handler();
void __key_handler();

#endif