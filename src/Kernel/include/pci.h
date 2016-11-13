#ifndef __PCI_H
#define __PCI_H

#include <stdint.h>

uint16_t __pci_config_read_word(uint8_t, uint8_t, uint8_t, uint8_t);
uint16_t __pci_check_vendor(uint8_t, uint8_t);

// robado

typedef struct {
            uint32_t portBase;
            uint32_t interrupt;

            uint8_t bus;
            uint8_t device;
            uint8_t function;

            uint16_t vendor_id;
            uint16_t device_id;

            uint8_t class_id;
            uint8_t subclass_id;
            uint8_t interface_id;

            uint8_t revision;
} PCIDescriptor_t;

typedef PCIDescriptor_t * PCIDescriptor;

typedef struct {
  uint8_t* address;
  uint32_t size;
  uint8_t type;
} BaseAddressRegister;


void findRTL();
void printPCID(PCIDescriptor);
PCIDescriptor_t getDescriptor(uint8_t bus, uint8_t device, uint8_t function);
BaseAddressRegister getBAR(uint8_t bus, uint8_t device, uint8_t function, uint16_t bar);
// ends robado
#endif
