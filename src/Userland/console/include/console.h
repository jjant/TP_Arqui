#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

void console_loop();
uint16_t parse_input(char *, uint16_t);
uint16_t execute_program(uint16_t);
uint16_t shell_invalid_input();
uint16_t shell_quit();
uint16_t shell_help();
uint16_t shell_echo();
void clean_buffer(char *, uint16_t);

#endif