#ifndef __PCI_H
#define __PCI_H

#include <stdint.h>
#include <stdint.h>
#include <ports.h>

#define PCI_CONFIG_ADDRESS  0x0CF8
#define PCI_CONFIG_DATA     0x0CFC

#define RTL_VENDOR_ID 0x10EC
#define RTL_DEVICE_ID 0x8139

#define INPUT_OUTPUT   1
#define MEMORY_MAPPING 0
#define NULL (void *)  0

void __os_pci_write_reg(uint8_t, uint8_t, uint16_t, uint64_t);
uint32_t __os_pci_read_reg(uint8_t, uint8_t, uint16_t);
void __DMA_init();

#endif
