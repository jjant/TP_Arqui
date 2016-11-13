#include <pci.h>
#include <stdint.h>
#include <ethernet.h>
#include <ports.h>
#include <memory.h>

static uint32_t cnfg_addr = 0xCF8;
static uint32_t cnfg_data = 0xCFC;

uint16_t __pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  uint32_t address;
  uint32_t lbus   = (uint32_t)bus;
  uint32_t lslot  = (uint32_t)slot;
  uint32_t lfunc  = (uint32_t)func;
  uint16_t tmp = 0;

  /* create configuration address as per Figure 1 */
  address = (uint32_t)(
            (lbus << 16)    |
            (lslot << 11)   |
            (lfunc << 8)    |
            (offset & 0xFC) | 
            ((uint32_t) 0x80000000));

  __outportdw(cnfg_addr, address);

  /* (offset & 2) * 8) = 0 will choose the first word of the 32 bits register */
  tmp = (uint16_t)(__inportdw(cnfg_data) >> ((offset & 2) * 8) & 0xFFFF);

  return tmp;
}

uint16_t __pci_check_vendor(uint8_t bus, uint8_t slot) {
  uint16_t vendor, device;
  /* If device is non-existent, the pci will return all ones. */
  if((vendor = __pci_config_read_word(bus, slot, 0, 0)) != 0xFFFF)
    device = __pci_config_read_word(bus, slot, 0, 2);

  return vendor;
}

PCI_Descriptor_t __get_descriptor(uint16_t bus, uint16_t device, uint16_t function) {
  PCI_Descriptor_t descriptor = __malloc(sizeof(PCI_Descriptor_t));

  descriptor->bus      = bus;
  descriptor->device   = device;
  descriptor->function = function;

  descriptor->vendor_id    = __pci_config_read_word(bus, device, function, 0x00)
  descriptor->device_id    = __pci_config_read_word(bus, device, function, 0x02);
  descriptor->class_id     = __pci_config_read_word(bus, device, function, 0x0B);
  descriptor->subclass_id  = __pci_config_read_word(bus, device, function, 0x0A);
  descriptor->interface_id = __pci_config_read_word(bus, device, function, 0x09);
  descriptor->revision     = __pci_config_read_word(bus, device, function, 0x08);
  descriptor->interrupt    = __pci_config_read_word(bus, device, function, 0x3C);

  return descriptor;
}

void print_all_devices() {
  uint16_t bus, device, function;

  for(bus = 0; bus < 8; bus++) {
    for(device = 0; device < 32; device++) {
      for(function = 0 ; function < 8; function++) {
        PCI_Descriptor_t descriptor = __get_descriptor(bus, device, function);

        if(descriptor->vendor_id == 0x00 || descriptor->vendor_id == 0xFFFF)
          return;

        __puts("PCI bus: ");
        __print_hex(bus & 0xFF);
        __puts(" , devise: ");
        __print_hex(device & 0xFF);
        __puts(" , function: ");
        __print_hex(function & 0xFF);
      }
    }
  }
}