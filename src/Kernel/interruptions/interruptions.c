#include <interruptions.h>
#include <handler.h>

#pragma pack(push)
#pragma pack(1)

typedef struct { 
	uint16_t offset_l; //bit 0..15
	uint16_t selector;
	uint8_t zero_l;
	uint8_t attrs;
	uint16_t offset_m; //16..31
	uint32_t offset_h; //32..63
	uint32_t zero_h;
} IDTEntry_t;

#pragma pack(pop)

static IDTEntry_t* IDT = (IDTEntry_t*) 0x0;

void __IDT_add_handler(int index, uint64_t handler) {
	IDT[index].offset_l = (uint16_t) handler & 0xFFFF;
	IDT[index].offset_m = (uint16_t) (handler >> 16) & 0xFFFF;
	IDT[index].offset_h = (uint32_t) (handler >> 32) & 0xFFFFFFFF;
	
	IDT[index].selector = 0x08;
	IDT[index].zero_l = 0;
	
	IDT[index].attrs = 0x8E;
	IDT[index].zero_h = 0;	
}

void __initialize_IDT() {
	__IDT_add_handler(0x20, (uint64_t) irq0Handler);
	__IDT_add_handler(0x21, (uint64_t) irq1Handler);
	__IDT_add_handler(0x2B, (uint64_t) irq11Handler);
}


void __int_2B() {
	__int_2B_asm();
}
