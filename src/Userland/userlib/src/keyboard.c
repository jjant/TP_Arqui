////////// REMOVE
#include <keyboard.h>

static char keycode_to_char[] = {
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P', '[',  ']', '\n', '\0',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';', '\'', '`', '\0', '\\',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ',', '.', '/', '\0', '*', '\0', ' '
};

char __key_pressed() {
	int keycode = 0;
	while(1) {
		if(keycode = __key_pressed_asm())
			return code_to_char(keycode);
	}
}

static char code_to_char(int keycode) {
	char Q_code = 0x10;
	char SPACE_code = 0x39;

	if(keycode >= Q_code && keycode <= SPACE_code)
		return keycode_to_char[keycode - Q_code];
	else
		return 0;
}