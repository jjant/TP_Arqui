#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>
#include <memory.h>

#define MESSAGES_BUFFER 30
#define NULL (void *) 0

void send_message(uint8_t, const char *);
char * read_message();
char * read_message_asm();

#endif