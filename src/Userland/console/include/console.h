#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>
#include <keyboard.h>
#include <network.h>

#define NULL (void *)0
#define MAX_ARGS		20
#define SEND_CMD_OFFSET 2
#define BCAST_CMD_OFFSET 2


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

void console_loop();
void print_shell_icon();
void cls();
void private_line(char *);
uint8_t set_color(uint8_t);
char ** parse_input(char *, char **);
uint16_t execute_program(struct program_s *, char **);
uint16_t shell_invalid_input(const char **);
uint16_t shell_quit(const char **);
uint16_t shell_help(const char **);
uint16_t shell_clean(const char **);
uint16_t shell_hear(const char **);
uint16_t shell_placeholder(const char **);
uint16_t shell_send(const char **);
uint16_t shell_color(const char **);
uint16_t shell_language(const char **);
uint16_t shell_text(const char **);
uint16_t shell_colorscheme(const char **);
uint16_t shell_null(const char **);
uint16_t shell_echo(const char **);
uint16_t shell_chat(const char **);
void clean_buffer(char *, uint16_t);

#endif
