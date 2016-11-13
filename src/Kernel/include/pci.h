#ifndef __PCI_H
#define __PCI_H

#include <stdint.h>
struct PCI_Descriptor{
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
};

typedef struct PCI_Descriptor * PCI_Descriptor_t;

uint16_t __pci_config_read_word(uint8_t, uint8_t, uint8_t, uint8_t);
uint16_t __pci_check_vendor(uint8_t, uint8_t);
PCI_Descriptor_t __get_descriptor(uint16_t, uint16_t, uint16_t);

//delete later
void print_all_devices();
#endif
