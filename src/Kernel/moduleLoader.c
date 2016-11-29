#include <stdint.h>
#include <lib.h>
#include <moduleLoader.h>
#include <video.h>

static void __load_module(uint8_t ** module, void * targetModuleAddress);
static uint32_t __read_uint32(uint8_t ** address);

void __load_modules(void * payloadStart, void ** targetModuleAddress)
{
	int i;
	uint8_t * currentModule = (uint8_t*)payloadStart;
	uint32_t moduleCount = __read_uint32(&currentModule);

	for (i = 0; i < moduleCount; i++)
		__load_module(&currentModule, targetModuleAddress[i]);
}

static void __load_module(uint8_t ** module, void * targetModuleAddress) {
	uint32_t moduleSize = __read_uint32(module);
	__memcpy(targetModuleAddress, *module, moduleSize);
	*module += moduleSize;
}

static uint32_t __read_uint32(uint8_t ** address)
{
	uint32_t result = *(uint32_t*)(*address);
	*address += sizeof(uint32_t);
	return result;
}
