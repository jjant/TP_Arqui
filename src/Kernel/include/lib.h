#ifndef __LIB_H
#define __LIB_H

#include <stdint.h>
#include <video.h>
#include <string.h>
#include <keyboard.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

#endif
