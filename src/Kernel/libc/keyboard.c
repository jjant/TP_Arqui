#include <keyboard.h>


#define BUFFER_SIZE 128
#define BACKSPACE 0x0E
#define CAPS 0x3B

static unsigned char keycode_to_char[] = {
  '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE, '\t',
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[',  ']', '\n', '\0',
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '\0', '\\',
  'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '\0', '*', '\0', ' ', CAPS,
};
static char buffer[BUFFER_SIZE] = {0};
static uint8_t last_pos = 0;
static uint8_t first_pos = 0;

char __push_key() {
  static uint8_t caps = 1;
	char key = code_to_char(__getchar());
  uint8_t isChar = key >= 'A' && key <= 'Z';
  
  // BEHAVIOR KEYS
  switch(key){
    case 0: return 0;
    case CAPS:
      caps = caps ? 0 : 1;
      return 0;
    case BACKSPACE:
      break;
  }

  // CAPS MANAGEMENT
  if (isChar && caps)
    key = key - 'A' + 'a';

  buffer[last_pos++] = key;
  last_pos %= BUFFER_SIZE;

  return 1;
}

char __pop_key() {
	char key = buffer[first_pos];
  buffer[first_pos++] = 0;
  first_pos %= BUFFER_SIZE;

	return key;
}

void __flush() {
	int i; 

	for (i = 0; i < BUFFER_SIZE; i++) {
		buffer[i] = 0;
	}

	last_pos = first_pos = 0;
}

char __key_pressed() {
	int keycode = 0;
	while(1) {
		if(keycode = __key_pressed_asm())
			return code_to_char(keycode);
	}
}

static char code_to_char(int keycode) {
	char Q_code = 0x2;
	char SPACE_code = 0x3A;

	if(keycode >= Q_code && keycode <= SPACE_code)
		return keycode_to_char[keycode - Q_code];
	else
		return 0;
}