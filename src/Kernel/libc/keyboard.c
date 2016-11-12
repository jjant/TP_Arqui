#include <keyboard.h>


#define BUFFER_SIZE 128
#define BACKSPACE 0x0E
#define CAPS 0x3B

static unsigned char keyboard_easteregg[] = {
  1, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE, '\t',
  'Q', 'U', 'I', 'E', 'R', 'O', ' ', 'A', 'P', 'R', '[',  ']', '\n', '\0',
  'O', 'B', 'A', 'R', ' ', 'A', 'R', 'Q', 'U', ';', '\'', '`', '\0', '\\',
  'I', ' ', 'P', 'L', 'I', 'S', '!', ',', '.', '/', '\0', '*', '\0', ' ', CAPS,
};

static unsigned char keyboard_english[] = {
  1, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE, '\t',
  'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[',  ']', '\n', '\0',
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '\0', '\\',
  'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '\0', '*', '\0', ' ', CAPS,
};

static unsigned char keyboard_dvorak[] = {
  1, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', BACKSPACE, '\t',
  '\'', ',', '.', 'P', 'Y', 'F', 'G', 'C', 'R', 'L', '?',  '+', '\n', '\0',
  'A', 'O', 'E', 'U', 'I', 'D', 'H', 'T', 'N', 'S', '\'', '`', '\0', '\\',
  ';', 'Q', 'J', 'K', 'X', 'B', 'M', 'W', 'V', 'Z', '\0', '*', '\0', ' ', CAPS,
};

static unsigned char special_keys[] = {
  ')', '!', '@', '#', '$', '?', '^', '&', '*', '('
};

static char buffer[BUFFER_SIZE] = {0};
static uint8_t last_pos = 0;
static uint8_t first_pos = 0;

static uint8_t current_keyboard = 0;

char __push_key() {
  static uint8_t caps = 1;
  static uint8_t shift = 0;
  int keycode = __getchar();

  if (keycode == 0x2A || keycode == 0x36) shift = 1;
  if (keycode == 0xAA || keycode == 0xB6) shift = 0;

	char key = code_to_char(keycode);
  uint8_t isChar = key >= 'A' && key <= 'Z';
  uint8_t isNumeric = key >= '0' && key <= '9';
  
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
  if (isChar && (caps && shift || !caps && !shift)) {
    key = key - 'A' + 'a';
  } else if (isNumeric && shift) {
    key = special_keys[key - '0'];
  }

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

void __change_keyboard(uint8_t keyboard_code) {
  current_keyboard = keyboard_code;
}

static char code_to_char(int keycode) {
	char Q_code = 0x1;
	char SPACE_code = 0x3A;

	if(keycode >= Q_code && keycode <= SPACE_code) {
    if (current_keyboard == 1) return keyboard_easteregg[keycode - Q_code];
    if (current_keyboard == 2) return keyboard_dvorak[keycode - Q_code];
    return keyboard_english[keycode - Q_code];
  } else return 0;
}