#include <console.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 128
#define HISTORY_SIZE 20
#define PROGRAM_COUNT 3

#define MAX_ARG_LEN 50
#define SHELL_QUIT 	1
#define SHELL_OK		0

#define BACKSPACE 0x0E

static struct program_s	programs[] = {
	{"QUIT", shell_quit},
	{"CLS", shell_clean},
	{"HELP", shell_help},
	{"ECHO", shell_echo},
	{NULL, shell_invalid_input}	// invalid input program determines the end of the programs array.
};

int main() {
	shell_clean(NULL);
	console_loop();

	return 0;
}

void console_loop() {
	char command_history[HISTORY_SIZE][BUFFER_SIZE];
	uint16_t command_history_index = 0;

	char command[BUFFER_SIZE] = { 0 };
	uint16_t current_index = 0;
	int c;

	while(1) {
		char args[MAX_ARG_LEN][MAX_ARGS]; //maybe use dynamic memory for this later.

		puts("$ > ");
		
		while((c = getchar()) != '\n') {
			if(c == BACKSPACE) {
				if (!current_index) continue;
				putc(BACKSPACE);
				command[--current_index] = 0;
			}
			else if (c) putc(command[current_index++] = c);
		}

		parse_input(command, args);
		execute_program(programs, args);	// args[0] is the name of the program to run.

		copy_buffer(command_history[command_history_index++ % HISTORY_SIZE], command, current_index);
		clean_buffer(command, current_index);
		current_index = 0;
	}
}

char ** parse_input(char * kb_buffer, char args[][MAX_ARGS]) {

	int k = 0;
	char * current = args[0];

	while(*kb_buffer) {
		if(*kb_buffer != ' ') {
			*current = *kb_buffer;
			current++;
		}
		else {
			*current = '\0';
			k++;
			current = args[k];
		}

		kb_buffer++;
	}

	*current = '\0';
	return args;
}

uint16_t execute_program(struct program_s * programs, char args[][MAX_ARGS]) {
	int i = 0;
	struct program_s current = programs[i];
	uint16_t ret_val;

	putc('\n');

  while(current.name) {
  	if(strcmp(current.name, args[0]) == 0) {
  		ret_val = current.fnc(args);
  		goto clean_up;
  	} 
  	else {
  		current = programs[++i];
  	}
	}
	ret_val = current.fnc(args);

	clean_up:	putc('\n');
	return ret_val;
}

uint16_t shell_invalid_input(const char ** args) {
	puts("Invalid input detected.");
	return SHELL_OK;
}

uint16_t shell_quit(const char ** args) {
	puts("Quitting shell.");
	return SHELL_QUIT;
}

uint16_t shell_help(const char ** args) {
	puts("Este es el program help.");
	return SHELL_OK;
}

uint16_t shell_echo(const char ** args) {
	puts("Este es el programa echo.");
	return SHELL_OK;
}

uint16_t shell_clean(const char ** args) {
	cls();
	return SHELL_OK;
}

void clean_buffer(char * kb_buffer, uint16_t size) {
	int i;
	for(i = 0; i < size; i++)
		kb_buffer[i] = '\0';
}

void copy_buffer(char * to_buffer, char * origin_buffer, uint16_t size) {
	int i;
	for(i = 0; i < size; i++)
		to_buffer[i] = origin_buffer[i];
}