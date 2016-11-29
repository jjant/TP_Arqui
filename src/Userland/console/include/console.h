#ifndef CONSOLE_H
#define CONSOLE_H

#include <stdint.h>
#include <keyboard.h>
#include <network.h>

#define NULL (void *)0
#define MAX_ARGS		20
#define SEND_CMD_OFFSET 2
#define BCAST_CMD_OFFSET 2


typedef uint16_t (* shell_program)(char ** const);

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
uint16_t shell_invalid_input(char ** const);
uint16_t shell_quit(char ** const);
uint16_t shell_help(char ** const);
uint16_t shell_clean(char ** const);
uint16_t shell_hear(char ** const);
uint16_t shell_placeholder(char ** const);
uint16_t shell_send(char ** const);
uint16_t shell_color(char ** const);
uint16_t shell_language(char ** const);
uint16_t shell_text(char ** const);
uint16_t shell_colorscheme(char ** const);
uint16_t shell_null(char ** const);
uint16_t shell_echo(char ** const);
uint16_t shell_chat(char ** const);
uint16_t shell_beatles(char ** const);
void clean_buffer(char *, uint16_t);
void copy_buffer(char *, char *, uint16_t);

#endif
