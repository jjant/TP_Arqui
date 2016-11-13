#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void __IDT_add_handler(int index, uint64_t handler);
void __initialize_IDT();
void __int_11();

#endif
