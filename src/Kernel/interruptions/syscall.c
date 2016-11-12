#include <syscall.h>
#include <interruptions.h>
#include <stdint.h>
#include <keyboard.h>
#include <video.h>

#define INTERRUPT_VECTOR	0x80
#define SYSCALL_SIZE 256

#define SYSCALL_PRIVATE_LINE  6
#define SYSCALL_KEYBOARD_LANGUAGE  5
#define SYSCALL_WRITE 4
#define SYSCALL_READ  3
#define SYSCALL_CLEAN_SCREEN  2
#define SYSCALL_SET_COLOR  1

static void __setup_syscalls();

typedef uint64_t (*syscall_t)();
typedef void (*__write_t)(char *, size_t);

static syscall_t syscall[SYSCALL_SIZE];

void __initialize_syscall_vector() {
	__IDT_add_handler(0x80, (uint64_t)__syscall_handler);
	__setup_syscalls();
}

static void __setup_syscalls() {
  syscall[SYSCALL_WRITE] = __write;
  syscall[SYSCALL_READ] = __keyboard_key;
  syscall[SYSCALL_CLEAN_SCREEN] = __clear_screen;
  syscall[SYSCALL_SET_COLOR] = __set_color;
  syscall[SYSCALL_KEYBOARD_LANGUAGE] = __change_keyboard;
	syscall[SYSCALL_PRIVATE_LINE] = __private_line;
}

void __syscall_dispatcher(int id, uint64_t first_parameter, uint64_t second_parameter) {
	(*syscall[id])(first_parameter, second_parameter);
}

char __keyboard_key() {
  return __pop_key();
}

void __write(char * str, size_t sz) {
	int i;

	for(i = 0; i < sz; i++)
		__putc(str[i]);
}

