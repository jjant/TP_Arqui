#include <keyboard.h>

#define KEYCODE_LEN		27

static char keycode_to_char[] = {
	'Q', 'W', 'E', 'R', 'T', 'Y', 'U', 'I', 'O', 'P',
	'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L',
	'Z', 'X', 'C', 'V', 'B', 'N', 'M', ' '
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
	char P_code = 0x19;
	char A_code = 0x1E;
	char L_code = 0x26;
	char Z_code = 0x2C;
	char M_code = 0x32;

	if(keycode >= Q_code && keycode <= P_code)
		return keycode_to_char[keycode - Q_code];
	else if (keycode >= A_code && keycode <= L_code)
		return keycode_to_char[keycode - 0x14];
	else if (keycode >= Z_code && keycode <= M_code)
		return keycode_to_char[keycode - 0x19];
	else if (keycode == 0x39)
		return keycode_to_char[KEYCODE_LEN - 1];
	else
		return 0;

}