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

	//initInterruptions();

	//checkAllBuses(0, 1);
	//deviceDetails(0, 0x18);
	//while(1);
	__initialize_IDT();
	__initialize_handlers();
	__initialize_syscall_vector();
	__set_pic_master_asm(0x00);
	__set_pic_slave_asm(0x0);
	sti();

	//Inicializo la DMA y el RTL 
	__DMA_init();
	//findRTL();
	__net_init();

	//rtlPrintMac();

	((EntryPoint)(0x400000))();

	return 0;
}

/*
int main() {
	uint16_t cmd_status;
	uint8_t mac_addr[6];
	char buffer[10];

	deviceDetails(0, 0x18);

	initInterruptions();
	__DMA_init();
	findRTL();
	rtl_init();
	rtcInit();

	rtlPrintMac();
	/*
	__clear_screen();
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
	__puts("[Configuring PIC]...");
	__set_pic_master(0xFC);
	__set_pic_slave(0x0);	//enable everything
	__puts("   Done.\n");
	__puts("[Initializing ethernet device]...");
	//__init_network();
	rtl_init();
	__puts("   Done.\n");
	/*
	__puts("Register status on rtl: 0x");

	cmd_status = __cmd_reg_value(__get_rtl_descriptor());
//  __print_hex((cmd_status & 0xFF00) >> 8);
  __print_hex(cmd_status & 0xFF);

	__puts("\n");
	__print_hex(__get_rtl_descriptor()->interrupt);
	*/

	//sti();

	//__puts("[Starting console]...\n");
	//	__print_rtl_status();

	//__puts("My mac address: ");
	//__print_own_mac();
	//__puts("\n");

	//__print_rtl_status();
	//print_all_devices();
	//_debug_rtl_handler();
	//__puts("Sending message to rtl...");
	//rtl_send("la concha de tu madre", 0x0);
	//__puts("   Done.\n");

	//__puts("mac addr:");

	/*
	__get_own_mac(mac_addr);

*/
	/*__get_own_mac(mac_addr);
	for (int i = 0; i < 6; ++i) {
		__print_hex(mac_addr[i]);
	}*/
	//__print_rtl_status();
	//rtlPrintMac();
	//_debug_rtl_handler();
	//_debug_rtl_handler();
	/*__int_2B();
	__int_2B();
	__int_2B();
	__int_2B();*/
	//__clear_screen();
	//__puts("rtl desc:\n");
	
	//((EntryPoint)0x400000)(); // Start the console
	//__puts("After console");
	
//	return 0;
//}
