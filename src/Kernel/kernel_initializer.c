#include <kernel_initializer.h>
#include <stdint.h>
#include <string.h>
#include <lib.h>
#include <moduleLoader.h>
#include <interruptions.h>
#include <syscall.h>
#include <video.h>

extern uint8_t text;
extern uint8_t rodata;
extern uint8_t data;
extern uint8_t bss;
extern uint8_t endOfKernelBinary;
extern uint8_t endOfKernel;

// Declare pagesize as 4KB. 
static const uint64_t PageSize = 0x1000;

static void * const console_module_address = (void*)0x400000;

typedef int (*EntryPoint)();

void clearBSS(void * bssAddress, uint64_t bssSize)
{
	memset(bssAddress, 0, bssSize);
}

void * getStackBase()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * __initialize_kernel_binary()
{
	__puts("[Loading modules]");
	__new_line();
	void * moduleAddresses[] = {
		console_module_address
	};
	loadModules(&endOfKernelBinary, moduleAddresses);
	__puts("[Done]");
	__new_line();
	__new_line();

	__puts("[Initializing kernel's binary]");
	__new_line();

	clearBSS(&bss, &endOfKernel - &bss);
/*
	ncPrint("  text: 0x");
	ncPrintHex((uint64_t)&text);
	ncNewline();
	ncPrint("  rodata: 0x");
	ncPrintHex((uint64_t)&rodata);
	ncNewline();
	ncPrint("  data: 0x");
	ncPrintHex((uint64_t)&data);
	ncNewline();
	ncPrint("  bss: 0x");
	ncPrintHex((uint64_t)&bss);
	ncNewline();

	ncPrint("[Done]");
	ncNewline();
*/

	return getStackBase();
}