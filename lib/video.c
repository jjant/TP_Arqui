#include <video.h>

static uint8_t * const video = (uint8_t *) 0xB8000;
static uint8_t * current_video = (uint8_t *) 0xB8000;
static const int width = 80;
static const int height = 25;

void clear_screen() {
	int i;
	for(i = 0; i < width * height; i++) {
		video[i * 2] = ' ';
	}
	current_video = video;
}

void clear_line(int line) {
	int i;
	for(i = 0; i < width; i++) {
		video[2 * (i + (line * width))] = ' ';
	}
}

void puts(const char * str) {
	int i = 0;
	for(i = 0; str[i] != '\0'; putc(str[i++]));
}

void putc(char c) {
	*current_video = c;
	current_video += 2;
}
