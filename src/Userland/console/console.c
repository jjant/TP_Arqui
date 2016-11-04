#include <console.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 128


void console_loop() {
	char buffer[BUFFER_SIZE];
	uint16_t current_index = 0;

	while(1) {
		puts("$ > ");
		break;
	}
}

int main() {
	console_loop();

	return 0;
}