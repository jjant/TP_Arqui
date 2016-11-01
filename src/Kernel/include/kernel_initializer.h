#ifndef __KERNER_INITIALIZER_H
#define __KERNER_INITIALIZER_H

#include <stdint.h>

void clearBSS(void *, uint64_t);
void * getStackBase();
void * __initialize_kernel_binary();

#endif