#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdlib.h>
#include <network.h>

#define BUFFER_SIZE 128
#define HISTORY_SIZE 20
#define PROGRAM_COUNT 3

#define MAX_ARG_LEN 50
#define MAX_ARGS		10
#define SHELL_QUIT  1
#define SHELL_OK    0
#define NULL (void *)0

#define BACKSPACE 0x0E
#define ESC 0x01

typedef uint16_t (* shell_program)(const char **);

struct program_s {
  const char *name;
  shell_program fnc;
	const char *help;
};

struct color_s {
  const char *name;
  const uint8_t code;
};

// Syscall functions
void cls();
void private_line(char *);
uint8_t set_color(uint8_t);

uint16_t shell_help(const char **);

#endif