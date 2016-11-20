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
	uint16_t cmd_status;

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

	__puts("[Configuring PIC]...");
	__set_pic_master(0xFC);
	__set_pic_slave(0x0);	//enable everything
	__puts("   Done.\n");
	__puts("Register status on rtl: 0x");

	cmd_status = __cmd_reg_value(__get_rtl_descriptor());
//  __print_hex((cmd_status & 0xFF00) >> 8);
  __print_hex(cmd_status & 0xFF);
	__puts("\n");
	__print_hex(__get_rtl_descriptor()->interrupt);
	sti();

	__puts("[Starting console]...\n");
	
	//print_all_devices();
	__int_2B();
	//((EntryPoint)0x400000)(); // Start the console

	return 0;
}
