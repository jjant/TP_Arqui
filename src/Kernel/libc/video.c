#include <video.h>

#define BACKSPACE 0x0E
#define WHITE_COLOR 7;
#define RED_COLOR 4

static uint8_t * const video = (uint8_t *) 0xB8000;
static uint8_t * current_video = (uint8_t *) 0xB8000;
static uint8_t current_color = WHITE_COLOR;
static uint8_t current_line = 1;
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

void __scroll() {
	int i; 
	
	// Copy last lines in the beggining
	for(i = width * 2 * 10; i < width * height * 2; i++) {
		video[i - width * 2 * 10] = video[i];
	}
	
	// Clean last lines
	for(i = width * 2 * (height - 10); i < width * height * 2; i += 2) {
		video[i] = ' ';
	}

	// Relocate cursor
	current_video = video + width * 2 * (height - 10);
}

uint8_t __set_color(uint8_t color) {
	uint8_t color_aux = current_color;
	current_color = color;
	return color_aux; 
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
	
	if(c == '\n') {
		uint8_t scroll_break = current_line == 25 || current_line > 25 && (current_line + 25) % 10 == 0;
		current_line++;

		if (scroll_break) {
			__scroll();
			return 0;
		}

		return __new_line();
	}

	*current_video = c;
	current_video++;
	*current_video = current_color;
	current_video++;
}

void __new_line() {
	do {
		__putc(' ');
	} while((uint64_t)(current_video - video) % (width * 2) != 0);
}