#ifndef _INTERRUPTIONS_H_
#define _INTERRUPTIONS_H_

#include <stdint.h>

void __IDT_add_handler(int index, uint64_t handler);

#endif
