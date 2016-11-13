#include <pci.h>

static uint32_t cnfg_addr = 0xCF8;
static uint32_t cnfg_data = 0xCFC;

uint16_t __pci_config_read_word(uint8_t bus, uint8_t slot, uint8_t func, uint8_t offset) {
  uint32_t address;
  uint32_t lbus   = (uint32_t)bus;
  uint32_t lslot  = (uint32_t)slot;
  uint32_t lfunc  = (uint32_t)func;
  uint16_t tmp = 0;

  /* create configuration address as per Figure 1 */
  address = (uint32_t)((lbus << 16) | (lslot << 11) |
            (lfunc << 8) | (offset & 0xFC) | ((uint32_t) 0x80000000));

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

// ROBADO DE MARCELO;

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

        }PCIDescriptor_t;

typedef PCIDescriptor_t * PCIDescriptor;

void findRTL(){
  __clear_screen();
  PCIDescriptor_t descriptor;
  int bus, device, function;

  for(bus = 0; bus < 256; bus++) {
     for(device = 0; device < 32; device++) {
        for(function = 0 ; function < 8; function++){
                
         descriptor = getDescriptor(bus, device, function);
         uint16_t vendorID = descriptor.vendor_id;
         uint16_t deviceID = descriptor.device_id;

         if(vendorID == RTL_VENDOR_ID || vendorID == RTL_DEVICE_ID){        // Device doesn't exist
            PCIDescriptor d = &descriptor;
            __puts("Found RTL8139");
            __new_line();
            __puts("BUS: 0x"); __print_hex(d->bus); __new_line();
            __puts("DEVICE: 0x"); __print_hex(d->device & 0xFF); __new_line();
            __puts("FUNCTION: 0x"); __print_hex(d->function & 0xFF); __new_line();
            __puts("Vendor ID: 0x"); __print_hex(d->vendor_id & 0xFFFF); __new_line();
            __puts("Device ID: 0x"); __print_hex(d->device_id & 0xFFFF); __new_line();
            __puts("Interrupt line 0x"); __print_hex(d->interrupt & 0xFF); __new_line();
            __puts("Interrupt pin 0x"); __print_hex((d->interrupt >> 8)& 0xFF); __new_line();
            __puts("Base port 0x"); __print_hex(d->portBase); __new_line();
            __new_line();
         }
  }
  }

  }
}

static int count = 0;
void printPCID(PCIDescriptor d){
    __puts("BUS: 0x"); 
    __print_hex(d->bus);

    __puts(" DEVICE: 0x"); 
    __print_hex(d->device & 0xFF);

    __puts(" FUNCTION: 0x"); 
    __print_hex(d->function & 0xFF);

    __puts(" Vendor ID: 0x"); 
    __print_hex(d->vendor_id & 0xFFFF);

    __puts(", Device ID: 0x"); 
    __print_hex(d->device_id & 0xFFFF);

    __puts("Interrupt 0x");
    __print_hex(d->interrupt);

    __new_line();
}

// Termina lo robado de marcelo.
