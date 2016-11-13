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
#include <pci.h>

typedef int (*EntryPoint)();

int main() {
	__new_line();
	__puts("[Initializing IDT]\n");
	__initialize_IDT();
	__puts("[Initializing interrupt handlers]\n");
	__initialize_handlers();
	__puts("[Initializing syscall vector]\n");
	__initialize_syscall_vector();

	setPicMaster(0xFC);
	sti();

	__puts("[Starting console...]\n");
	
	//print_all_devices();
	//__int_11();
	//findRTL();
	//((EntryPoint)0x400000)(); // Start the console

	return 0;
}
