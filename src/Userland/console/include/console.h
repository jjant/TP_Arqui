#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>

#define NULL (void *)0
#define MAX_ARGS		5

typedef uint16_t (* shell_program)(const char **);

struct program_s {
	const char *name;
  shell_program fnc;
};

void console_loop();
void cls();
char ** parse_input(char *, char [][MAX_ARGS]);
uint16_t execute_program(struct program_s *, char [][MAX_ARGS]);
uint16_t shell_invalid_input(const char **);
uint16_t shell_quit(const char **);
uint16_t shell_help(const char **);
uint16_t shell_clean(const char **);
uint16_t shell_echo(const char **);
void clean_buffer(char *, uint16_t);

#endif