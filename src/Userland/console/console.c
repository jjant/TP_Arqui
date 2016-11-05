#include <console.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 128
#define PROGRAM_COUNT 3

#define MAX_ARG_LEN 50
#define SHELL_QUIT 	1
#define SHELL_OK		0

static struct program_s	programs[] = {
	{"QUIT", shell_quit},
	{"HELP", shell_help},
	{"ECHO", shell_echo},
	{NULL, shell_invalid_input}	// invalid input program determines the end of the programs array.
};

int main() {
	console_loop();

	return 0;
}

void console_loop() {
	char buffer[BUFFER_SIZE] = { 0 };
	int c;
	uint16_t current_index = 0;

	while(1) {
		char args[MAX_ARG_LEN][MAX_ARGS]; //maybe use dynamic memory for this later.

		puts("$ > ");
		
		while((c = __key_pressed()) != '\n'){
			if(c != 0)
				putc(buffer[current_index++] = c);
		}
		buffer[current_index] = '\0';

		parse_input(buffer, args);


		puts("PASE EL PARSE\n");
		puts("ARG[0]=");
		puts(args[0]);
		putc('\n');

		execute_program(programs, args);	// args[0] is the name of the program to run.

		puts("Pase execute\n");
		clean_buffer(buffer, current_index);
		current_index = 0;
	}
}

char ** parse_input(char * kb_buffer, char args[][MAX_ARGS]) {
/*
	int i, j, k;
	for(i = 0, j = 0, k = 0; i <= size; i++) {
		if(i == size) {
			args[k]
		}
		if(kb_buffer[i] == ' ') {
			args[k][j] = '\0';
			k++;
			j = 0;
		}
		else {
			args[k][j++] = kb_buffer[i];
		}
	}
*/

/*
	int k;
	int iteration_complete = 0;
	for(k = 0; *kb_buffer && !iteration_complete; k++) {
		char * name = args[k];
		int name_found = 0;
		int i;

		for(i = 0; kb_buffer[i] && !name_found; i++) {
			if(kb_buffer[i] == ' ')
				name_found = 1;
			else
				name[i] = kb_buffer[i];
		}
		//CON el buffer con "hola", aca sale con i en 4.
		//Con el buffer en  
		puts("\nAca i es: ");
		putc(i + '0');
		putc("\n");
		name[i] = '\0';

		if(kb_buffer[i] != '\0')
			kb_buffer += i;
		else
			iteration_complete = 1;
	}
*/

	int k = 0;
	char * current = args[0];
	putc('\n');
	puts("buffer: ");
	puts(kb_buffer);

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
	if(current != NULL)
		*current = '\0';


	////DEBUG
	putc('\n');
	puts("args[0]: ");
	puts(args[0]);
	putc('\n');
	puts("arg[1]: ");
	puts(args[1]);
	putc('\n');
	puts("arg[2]: ");
	puts(args[2]);
	putc('\n');
	////
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

void clean_buffer(char * kb_buffer, uint16_t size) {
	int i;
	for(i = 0; i < size; i++)
		kb_buffer[i] = '\0';
}