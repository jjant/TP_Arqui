#include <console.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 128
#define PROGRAM_COUNT 3

#define QUIT_PID 					0
#define INVALID_INPUT_PID 1
#define HELP_PID					2

#define SHELL_QUIT -1
#define SHELL_OK	0

static void initialize_program_vector();

typedef uint16_t (* shell_program)();

static shell_program programs[PROGRAM_COUNT];

int main() {
	initialize_program_vector();
	console_loop();

	return 0;
}

void console_loop() {
	char buffer[BUFFER_SIZE] = { 0 };
	int c;
	uint16_t current_index = 0;

	while(1) {
		uint16_t pid;
		
		puts("$ > ");
		
		while((c = __key_pressed()) != '\n'){
			if(c != 0)
				putc(buffer[current_index++] = c);
		}

		pid = parse_input(buffer, current_index);
		execute_program(pid);
		clean_buffer(buffer, current_index);
		current_index = 0;
	}
}

static void initialize_program_vector() {
	programs[QUIT_PID] = shell_quit;
	programs[INVALID_INPUT_PID] = shell_invalid_input;
	programs[HELP_PID] = shell_help;
}

uint16_t parse_input(char * kb_buffer, uint16_t size) {
	if(strcmp(kb_buffer, "HELP") == 0)
		return HELP_PID;
	if(strcmp(kb_buffer, "QUIT") == 0)
		return QUIT_PID;
	return INVALID_INPUT_PID;
}

uint16_t execute_program(uint16_t pid) {
	uint16_t ret_value;
	
	putc('\n');
	ret_value = programs[pid]();
	putc('\n');

	return ret_value;
}

uint16_t shell_invalid_input() {
	puts("Invalid input detected.");
	return SHELL_OK;
}

uint16_t shell_quit() {
	puts("Quitting shell.");
	return SHELL_QUIT;
}

uint16_t shell_help() {
	puts("Este es el program help.");
	return SHELL_OK;
}

void clean_buffer(char * kb_buffer, uint16_t size) {
	int i;
	for(i = 0; i < size; i++)
		kb_buffer[i] = '\0';
}