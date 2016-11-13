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
	__puts("[Initializing IDT]...");
	__initialize_IDT();
	__puts("   Done.\n");
	__puts("[Initializing interrupt handlers]...");
	__initialize_handlers();
	__puts("   Done.\n");
	__puts("[Initializing syscall vector]...");
	__initialize_syscall_vector();
	__puts("   Done.\n");
	__puts("[Initializing ethernet device]...");
	__init_network();
	__puts("   Done.\n");

	__set_pic_master(0xFC);
	__set_pic_slave(0x0);	//enable everything

	sti();

	__puts("[Starting console]...\n");
	
	print_all_devices();
	__int_11();
	//findRTL();
	//((EntryPoint)0x400000)(); // Start the console

	return 0;
}
