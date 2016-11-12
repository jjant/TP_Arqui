#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <interruptions.h>
#include <syscall.h>
#include <handler.h>
#include <keyboard.h>
#include <kernel_initializer.h>
#include <ethernet.h>

typedef int (*EntryPoint)();

int main() {
	__new_line();
	__puts("[Initializing interrupt handlers]");
	__IDT_add_handler(0x20, (uint64_t) irq0Handler);
	__IDT_add_handler(0x21, (uint64_t) irq1Handler);
	__initialize_handlers();
	__new_line();
	__initialize_syscall_vector();
	__puts("[Initializing syscall vector]");
	__new_line();

	setPicMaster(0xFC);
	sti();

	__puts("[Starting console...]");
	__new_line();
	__new_line();
	
	((EntryPoint)0x400000)(); // Start the console

	return 0;
}
