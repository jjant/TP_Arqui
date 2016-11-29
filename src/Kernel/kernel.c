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

#define __console	((EntryPoint)(0x400000))

typedef int (*EntryPoint)();

int main() {
	__initialize_IDT();
	__initialize_handlers();
	__initialize_syscall_vector();
	__set_pic_master_asm(0x00);
	__set_pic_slave_asm(0x0);
	__sti();
	__DMA_init();
	__net_init();
	__console();
	return 0;
}
