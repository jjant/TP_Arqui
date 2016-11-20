#ifndef CHAT_H
#define CHAT_H

#define MAX_ARGS 2
#define MAX_ARG_LEN 200
#define MAX_MESSAGE_LEN 200
#define NO_MESSAGES -2
#define USUARIO 0

#define BACKSPACE 0x0E
#define ESC 0x01

#include <string.h>

void chat_program();
void talk_program(uint8_t);
uint8_t set_color(uint8_t);
void send_message(char *, uint8_t);
void receive_program();

#endif