#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <naiveConsole.h>
#include <interruptions.h>
#include <syscall.h>
#include <handler.h>
#include <kernel_initializer.h>

typedef int (*EntryPoint)();

int main() {
	__initialize_syscall_vector();
	__IDT_add_handler(0x20, (uint64_t) irq0Handler);
	__initialize_handlers();
	ncPrintHex(((EntryPoint)0x400000)());
	

	setPicMaster(0xFE);
	sti();
	
	while(1)
		__putc(__key_pressed());
	
	return 0;
}
