#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

#define NULL (void *)0
#define MAX_ARGS		50

typedef uint16_t (* shell_program)(const char **);

struct program_s {
	const char *name;
  shell_program fnc;
};

void console_loop();
void print_shell_icon();
void cls();
uint8_t set_color(uint8_t);
char ** parse_input(char *, char [][MAX_ARGS]);
uint16_t execute_program(struct program_s *, char [][MAX_ARGS]);
uint16_t shell_invalid_input(const char [][MAX_ARGS]);
uint16_t shell_quit(const char [][MAX_ARGS]);
uint16_t shell_help(const char [][MAX_ARGS]);
uint16_t shell_clean(const char [][MAX_ARGS]);
uint16_t shell_color(const char [][MAX_ARGS]);
uint16_t shell_language(const char [][MAX_ARGS]);
uint16_t shell_colorscheme(const char [][MAX_ARGS]);
uint16_t shell_null(const char [][MAX_ARGS]);
uint16_t shell_echo(const char [][MAX_ARGS]);
void clean_buffer(char *, uint16_t);

#endif