#include <syscall.h>
#include <interruptions.h>
#include <stdint.h>
#include <rtl.h>
#include <keyboard.h>
#include <memory.h>
#include <video.h>

#define INTERRUPT_VECTOR	0x80
#define SYSCALL_SIZE 256

#define SYSCALL_GET_ID_NETWORK      16
#define SYSCALL_CLEAR_MESSAGE       10
#define SYSCALL_READ_MESSAGE        9
#define SYSCALL_SEND_MESSAGE        8
#define SYSCALL_RESERVE_MEMORY      7
#define SYSCALL_PRIVATE_LINE        6
#define SYSCALL_KEYBOARD_LANGUAGE   5
#define SYSCALL_WRITE               4
#define SYSCALL_READ                3
#define SYSCALL_CLEAN_SCREEN        2
#define SYSCALL_SET_COLOR           1

static void __setup_syscalls();

typedef uint64_t (*syscall_t)();
typedef void (*__write_t)(char *, size_t);

static syscall_t syscall[SYSCALL_SIZE];

void __initialize_syscall_vector() {
	__IDT_add_handler(0x80, (uint64_t)__syscall_handler);
	__setup_syscalls();
}

static void __setup_syscalls() {
  syscall[SYSCALL_WRITE]              = (syscall_t)__write;
  syscall[SYSCALL_READ]               = (syscall_t)__keyboard_key;
  syscall[SYSCALL_CLEAN_SCREEN]       = (syscall_t)__clear_screen;
  syscall[SYSCALL_SET_COLOR]          = (syscall_t)__set_color;
  syscall[SYSCALL_KEYBOARD_LANGUAGE]  = (syscall_t)__change_keyboard;
  syscall[SYSCALL_PRIVATE_LINE]       = (syscall_t)__private_line;
	syscall[SYSCALL_RESERVE_MEMORY]     = (syscall_t)__malloc;
  syscall[SYSCALL_GET_ID_NETWORK]     = (syscall_t)__net_id;
  syscall[SYSCALL_CLEAR_MESSAGE]      = (syscall_t)__net_clear;
  syscall[SYSCALL_READ_MESSAGE]       = (syscall_t)__net_read;
  syscall[SYSCALL_SEND_MESSAGE]       = (syscall_t)__net_send;
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
