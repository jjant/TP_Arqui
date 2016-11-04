#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <interruptions.h>
#include <syscall.h>
#include <handler.h>
#include <kernel_initializer.h>

typedef int (*EntryPoint)();

int main() {
	__new_line();
	__puts("Initializing interrupt handlers.");
	__new_line();
	__initialize_syscall_vector();
	__puts("initialized syscall vector");

	__IDT_add_handler(0x20, (uint64_t) irq0Handler);
	__initialize_handlers();
	__new_line();
	__puts("Interrupt handlers initialized.");
	__new_line();

	setPicMaster(0xFE);
	sti();

	__new_line();
	__new_line();
	__puts("[Starting console...]");
	__new_line();
	__new_line();
	
	((EntryPoint)0x400000)();

	while(1)
		__putc(__key_pressed());
	
	return 0;
}
