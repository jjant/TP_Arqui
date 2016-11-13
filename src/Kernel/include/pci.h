#ifndef __PCI_H
#define __PCI_H

uint16_t __pci_config_read_word(uint8_t, uint8_t, uint8_t, uint8_t);
uint16_t __pci_check_vendor(uint8_t, uint8_t);

// robado
void findRTL();
void printPCID(PCIDescriptor);
// ends robado
#endif
