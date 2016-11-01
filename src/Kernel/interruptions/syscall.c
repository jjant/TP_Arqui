#include <syscall.h>
#include <interruptions.h>
#include <stdint.h>
#include <video.h>

#define INTERRUPT_VECTOR	0x80
#define SYSCALL_WRITE 0
#define SYSCALL_READ 	1

static void __setup_syscalls();

typedef uint64_t (*syscall_t)();
typedef void (*__write_t)(char *, size_t);

static syscall_t syscall[2];

void __initialize_syscall_vector() {
	__IDT_add_handler(0x80, (uint64_t)__syscall_handler);
	__setup_syscalls();
}

static void __setup_syscalls() {
	syscall[0] = __write;
}

void __syscall_dispatcher(int id, uint64_t first_parameter, uint64_t second_parameter) {
	(*syscall[id])(first_parameter, second_parameter);
}

void __write(char * str, size_t sz) {
	int i;

	for(i = 0; i < sz; i++)
		__putc(str[i]);
}

