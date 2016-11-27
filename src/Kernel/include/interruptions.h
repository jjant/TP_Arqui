#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void iSetHandler(int index, uint64_t handler);
void initInterruptions(void);


void setPIC();

void sti();
void irq0Handler();
void irq1Handler();
void irq11Handler();


#endif


#define __ignore_code
#ifndef __ignore_code

#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void __IDT_add_handler(int index, uint64_t handler);
void __initialize_IDT();
void __int_2B();

#endif

#endif
