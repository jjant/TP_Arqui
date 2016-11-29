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

void __clear_BSS(void * bssAddress, uint64_t bssSize)
{
	__memset(bssAddress, 0, bssSize);
}

void * __get_stack_base()
{
	return (void*)(
		(uint64_t)&endOfKernel
		+ PageSize * 8				//The size of the stack itself, 32KiB
		- sizeof(uint64_t)			//Begin at the top of the stack
	);
}

void * __initialize_kernel_binary()
{
	__puts("[Loading modules]\n");
	void * moduleAddresses[] = {
		console_module_address
	};
	__load_modules(&endOfKernelBinary, moduleAddresses);
	__puts("[Done]\n");
	__puts("[Initializing kernel's binary]\n");

	__clear_BSS(&bss, &endOfKernel - &bss);
	return __get_stack_base();
}
