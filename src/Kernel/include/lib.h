#ifndef __LIB_H
#define __LIB_H

#include <stdint.h>
#include <video.h>
#include <string.h>
#include <clock.h>

void * memset(void * destination, int32_t character, uint64_t length);
void * memcpy(void * destination, const void * source, uint64_t length);

char *cpuVendor(char *result);

#endif