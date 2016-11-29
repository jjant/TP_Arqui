#ifndef __KERNER_INITIALIZER_H
#define __KERNER_INITIALIZER_H

#include <stdint.h>

void __clear_BSS(void *, uint64_t);
void * __get_stack_base();
void * __initialize_kernel_binary();

#endif
