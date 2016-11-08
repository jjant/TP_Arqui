#include <video.h>

#define BACKSPACE 0x0E

static uint8_t * const video = (uint8_t *) 0xB8000;
static uint8_t * current_video = (uint8_t *) 0xB8000;
static const int width = 80;
static const int height = 25;

void __clear_screen() {
	int i;
	for(i = 0; i < width * height; i++) {
		video[i * 2] = ' ';
	}
	current_video = video;
}

void __clear_line(int line) {
	int i;
	for(i = 0; i < width; i++) {
		video[2 * (i + (line * width))] = ' ';
	}
}

void __puts(const char * str) {
	int i = 0;
	for(i = 0; str[i] != '\0'; __putc(str[i++]));
}

void __putc(int c) {
	if(!c) return;

	if (c == BACKSPACE) {
		current_video -= 2;
		*(current_video) = ' ';
		return;
	}
	
	if(c == '\n')
		return __new_line();

	*current_video = c;
	current_video += 2;
}

void __new_line() {
	do {
		__putc(' ');
	} while((uint64_t)(current_video - video) % (width * 2) != 0);
}