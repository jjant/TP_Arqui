#include <video.h>
#include <stdint.h>

#define BACKSPACE 0x0E
#define WHITE_COLOR 7;
#define RED_COLOR 4

static uint32_t __uint_to_base(uint64_t, char *, uint32_t);
static void __private_line_paint();

static uint8_t * const private_video = (uint8_t *) (0xB8000);
static uint8_t * const video = (uint8_t *) (0xB8000 + 80 * 4);
static uint8_t * current_video = (uint8_t *) (0xB8000 + 80 * 4);
static uint8_t current_color = WHITE_COLOR;
static const int width = 80;
static const int height = 23;
static char buffer[64];

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

// Color private line
static void __private_line_paint() {
	int i;
	for (i = 1; i < width * 2; i += 2) {
		private_video[i] = current_color << 4;
	}

}

void __private_line(char * str) {
	int i;

	// Clean private line
	for(i = 0; i < width * 2; i += 2) {
		private_video[i] = ' ';
	}

	__private_line_paint();

	// Copy text
	i = 0;
	while(*str) {
		private_video[i += 2] = *str;
		str++;
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
	__private_line_paint();
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
		if ((current_video - video) / (2 * 80) == height - 1) {
			__scroll();
			return;
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

void __print_hex(uint64_t value) {
	__print_base(value, 16);
}

void __print_base(uint64_t value, uint32_t base) {
    __uint_to_base(value, buffer, base);
    __puts(buffer);
}

static uint32_t __uint_to_base(uint64_t value, char * buffer, uint32_t base) {
	char *p = buffer;
	char *p1, *p2;
	uint32_t digits = 0;

	//Calculate characters for each digit
	do {
		uint32_t remainder = value % base;
		*p++ = (remainder < 10) ? remainder + '0' : remainder + 'A' - 10;
		digits++;
	}	while (value /= base);

	// Terminate string in buffer.
	*p = 0;

	//Reverse string in buffer.
	p1 = buffer;
	p2 = p - 1;
	while (p1 < p2) {
		char tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}

	return digits;
}

