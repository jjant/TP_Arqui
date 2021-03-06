#include <console.h>
#include <string.h>
#include <stdint.h>
#include <memory.h>

#define BUFFER_SIZE 128
#define HISTORY_SIZE 20
#define PROGRAM_COUNT 3

#define MAX_ARG_LEN 50
#define SHELL_QUIT 	1
#define SHELL_OK		0

#define BACKSPACE 0x0E
#define ESC 0x01

static struct program_s	programs[] = {
	{"QUIT",        shell_quit, "No recibe parametros."},
  {"CLS",         shell_clean, "No recibe parametros."},
  {"COLOR",       shell_color, "Los colores disponibles son: AMARILLO, LIMA, TURQUESA, GRIS, BLANCO, FUCSIA, NARANJA, CELESTE, VERDE, AZUL, PIEDRA, ROSA, ARCILLA y NEGRO."},
  {"COLORSCHEME", shell_colorscheme, "Los esquemas disponibles son: RIBER, BOCA y PATRIA."},
  {"TEXT",        shell_text, "Presiona ESC para salir del editor"},
  {"SEND",        shell_send, "IDs disponibles de acuerdo a las instancias del SO abiertas."},
  {"HEAR",        shell_hear, "No recibe parametros."},
  {"KEYBOARD",    shell_language, "Los teclados disponibles son: ENGLISH, DVORAK y EASTER. Presiona ESC para volver al teclado default."},
  {"HELP",        shell_help, "Recurrencia, recursion o recursividad es la forma en la cual se especifica un proceso basado en su propia definicion"},
  {"ECHO",        shell_echo, "Los mensajes deben ir entre comillas simples 'MENSAJE'"},
  {"PLACEHOLDER", shell_placeholder, "Manda el placeholder nuevo por argumento"},
  {"BEATLES",     shell_beatles, "Conoce un poco de los Beatles"},
  {"",            shell_null, ""},
  {NULL,          shell_invalid_input, ""}
};

static uint8_t console_color = 4;
static char * console_placeholder = "ARQ PC";

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
	private_line("CONSOLE");
	while(1) {

		char ** args = malloc(MAX_ARGS * sizeof (char *));
		for(int i = 0; i < MAX_ARGS; i++) {
			void * aux = malloc(MAX_ARG_LEN);
			args[i] = (char *) aux;
		}

		print_shell_icon(&console_color);

		while((c = getchar()) != '\n') {
			if(c == BACKSPACE) {
				if (!current_index) continue;
				putc(BACKSPACE);
				command[--current_index] = 0;
			}
			else if (c == ESC) set_keyboard_language(0);
			else if (c) putc(command[current_index++] = c);
		}

		parse_input(command, args);
		private_line(args[0]);
		execute_program(programs, args);	// args[0] is the name of the program to run.

		copy_buffer(command_history[command_history_index++ % HISTORY_SIZE], command, current_index);
		clean_buffer(command, current_index);
		current_index = 0;
	}
}

void print_shell_icon() {
	uint8_t color = set_color(console_color);
	printf(" %s %c ", console_placeholder, 26);
	set_color(color);
}

char ** parse_input(char * kb_buffer, char ** args) {
  int k = 0;
  char * current = args[0];
  uint8_t in_string = 0;

  while(*kb_buffer) {
    if (k > 0 && *kb_buffer == '\'') {
      in_string = in_string ? 0 : 1;
      kb_buffer++;
      continue;
    }

    if(*kb_buffer != ' ' || (in_string && *kb_buffer == ' ')) {
      *current = *kb_buffer;
      current++;
    } else if (!in_string) {
      *current = '\0';
      k++;
      current = args[k];
    }

    kb_buffer++;
  }

  *current = '\0';
  args[k + 1] = NULL;
  return args;
}

uint16_t execute_program(struct program_s * programs, char ** args) {
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

	clean_up:	//putc('\n');
	return ret_val;
}

uint16_t shell_invalid_input(char ** const args) {
	puts(" Invalid input detected.");
	putc('\n');
	return SHELL_OK;
}

uint16_t shell_quit(char ** const args) {
	puts(" Quitting shell.");
	putc('\n');
	return SHELL_QUIT;
}

uint16_t shell_placeholder(char ** const args) {
  if (args[1]) console_placeholder = args[1];
  return SHELL_OK;
}

uint16_t shell_echo(char ** const args) {
  if (args[1]) printf(" %s", args[1]);
	putc('\n');
	return SHELL_OK;
}

uint16_t shell_help(char ** const args) {
  int i = -1;
  while(programs[++i].name) {
    if (strcmp(programs[i].name, args[1]) == 0) {
      printf(" %s\n", programs[i].help);
      putc('\n');
      return SHELL_OK;
    }
  }

  puts(" HELP -- Ayuda al usuario \n\n");
  
  puts(" 1. SO es case sensitive.\n");
  puts(" 2. SO es simple.\n");
  puts(" 3. SO es aprobable.\n\n");

  puts(" COLOR <COLOR>: Cambia el color del texto\n");
  puts(" COLORSCHEME <SCHEME>: Cambia el color del esquema de la consola\n");
  puts(" KEYBOARD <KEYBOARD>: Cambia el teclado\n");
  puts(" CLS: Limpia la pantalla\n");
  puts(" TEXT: Editor de texto basico\n");
  puts(" ECHO <MENSAJE>: Repite el mensaje del usuario\n");
  puts(" PLACEHOLDER <MENSAJE>: Cambia el placeholder por defecto por uno custom\n");
  puts(" HELP : Programa de ayuda\n");
  puts(" HEAR: Entrar en modo recepción de mensajes\n");
  puts(" SEND <ID|ALL> 'MENSAJE': Enviar o broadcastear un mensaje\n");
  puts(" BEATLES: Una buena cancion\n\n");
  
  puts(" Para saber mas de un programa, usa HELP <PROGRAMA>\n");

  return SHELL_OK;
}

uint16_t shell_text(char ** const args) {
	char c;
	cls();
	
	while(1) {
		c = getchar();
		if(c == BACKSPACE) putc(BACKSPACE);
		else if (c == ESC) break;
		else if (c) putc(c);
	}
	
	putc('\n');
	return SHELL_OK;
}

uint16_t shell_send(char ** const args) {
	if (args[1]) {
		net_clear();
		if (strcmp(args[1], "WHOAMI") == 0) {
			printf(" Sos el usuario %d", net_id());
			putc('\n');
			return SHELL_OK;
		}	else if (strcmp(args[1], "ALL") == 0) {
			net_broadcast(args[2]);
			return SHELL_OK;
		}

		net_send(args[2], atoi(args[1]));
		return SHELL_OK;
	}

	printf(" Debe mandar los parametros adecuados");
	putc('\n');

	return SHELL_OK;
}

uint16_t shell_hear(char ** const args) {
	char buffer[1000];
	typedef struct{
	  int is_broadcast;
	  int user;
	} message_meta_t;

	message_meta_t message_info;
  if(!net_read(buffer, (void *) &message_info, 1000)){
    printf(" El buzon esta vacio");
    putc('\n');
  }else{
    do{
      if(*buffer != 0) {
  	    printf(" %s %d: %s", message_info.is_broadcast ? "PUBLIC" : "PRIVATE", message_info.user, buffer);
  			putc('\n');
      }
    } while(net_read(buffer, (void *) &message_info, 1000));
  }

	return SHELL_OK;
}

uint16_t shell_color(char ** const args) {
  static struct color_s colors[] = {
    {"NEGRO",     0},
    {"AZUL",      1},
    {"VERDE",     2},
    {"PIEDRA",    3},
    {"ROJO",      4},
    {"FUCSIA",    5},
    {"NARANJA",   6},
    {"BLANCO",    7},
    {"GRIS",      8},
    {"TURQUESA",  9},
    {"LIMA",     10},
    {"CELESTE",  11},
    {"ARCILLA",  12},
    {"ROSA",     13},
    {"AMARILLO", 14},
    {NULL,        7}
  };

  int i = -1;
  while (colors[++i].name) {
    if(strcmp(colors[i].name, args[1]) == 0) {
      set_color(colors[i].code);
      return SHELL_OK;
    }
  }
  
  puts(" Color no detectado. \n");
  return SHELL_OK;
}

uint16_t shell_colorscheme(char ** const args) {
	
	if(strcmp(args[1], "RIBER") == 0) { 			set_color(7); console_color = 4; }
	else if(strcmp(args[1], "BOCA") == 0) { 	set_color(1); console_color = 14; }
	else if(strcmp(args[1], "PATRIA") == 0) { set_color(3); console_color = 7; }
	else puts(" Esquema de color no encontrado. \n");

	return SHELL_OK;
}

uint16_t shell_clean(char ** const args) {
	cls();
	return SHELL_OK;
}

uint16_t shell_language(char ** const args) {

	if(strcmp(args[1], "ENGLISH") == 0) 		set_keyboard_language(0);
	else if(strcmp(args[1], "EASTER") == 0) set_keyboard_language(1);
	else if(strcmp(args[1], "DVORAK") == 0) set_keyboard_language(2);
	else puts(" Lenguaje no reconocido. \n");

	return SHELL_OK;
}

uint16_t shell_null(char ** const args) {
	return SHELL_OK;
}

uint16_t shell_beatles(char ** const args) {
  puts(" Help! I need somebody\n");
  puts(" Help! not just anybody\n");
  puts(" Help! you know i need someone\n");
  puts(" Help! when i was younger, so much younger than today\n");
  puts(" I never needed anybody's help in any way\n");
  puts(" But now these days are gone i'm not so self assured\n");
  puts(" Now i findi've changed my mind, i've opened up the doors\n");
  puts(" Help me if you can, i'm feeling down\n");
  puts(" And i do appreciate you being 'round\n");
  puts(" Help me get my feet back on the ground\n");
  puts(" Won't you please, please help me?\n");
  puts(" And now my life has changed in oh so many ways\n");
  puts(" My independence seems to vanish in the haze\n");
  puts(" But every now and then i feel so insecure\n");
  puts(" I know that i just need you like i've never done before\n");

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

