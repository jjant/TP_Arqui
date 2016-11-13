#include <pci.h>
#include <stdint.h>
#include <ethernet.h>
#include <ports.h>

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
#define INPUT_OUTPUT 1
#define MEMORY_MAPPING 0

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

         printPCID(&descriptor);
         __clear_screen();
         if(vendorID == __rtl_vendor_id() || vendorID == __rtl_device_id()){        // Device doesn't exist
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
            return;
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
    //__print_hex(d->device_id & 0xFFFF);

    __puts("Interrupt 0x");
    //__print_hex(d->interrupt);

    __new_line();
}

PCIDescriptor_t getDescriptor(uint8_t bus, uint8_t device, uint8_t function){
    PCIDescriptor_t result;
    int barNum;

    result.bus = bus;
    result.device = device;
    result.function = function;

    result.vendor_id = __pci_config_read_word(bus, device, function, 0x00);
    result.device_id = __pci_config_read_word(bus, device, function, 0x02);

    result.class_id = __pci_config_read_word(bus, device, function, 0x0b);
    result.subclass_id = __pci_config_read_word(bus, device, function, 0x0a);
    result.interface_id = __pci_config_read_word(bus, device, function, 0x09);

    result.revision = __pci_config_read_word(bus, device, function, 0x08);
    result.interrupt = __pci_config_read_word(bus, device, function, 0x3c);

    for(barNum = 0; barNum < 6; barNum++)
                {
                    BaseAddressRegister bar = getBAR(bus, device, function, barNum);
                    if(bar.address && (bar.type == INPUT_OUTPUT))
                        result.portBase = (uint32_t)bar.address;
                }

    return result;
}

BaseAddressRegister getBAR(uint8_t bus, uint8_t device, uint8_t function, uint16_t bar){

    BaseAddressRegister result;
    result.address = 0;

    uint32_t headertype = __pci_config_read_word(bus, device, function, 0x0E) & 0x7F;
    int maxBARs = 6 - (4*headertype);

    if(bar >= maxBARs)
        return result;

    uint32_t bar_value = __pci_config_read_word(bus, device, function, 0x10 + 4*bar);
    result.type = (bar_value & 0x1) ? INPUT_OUTPUT : MEMORY_MAPPING;
    uint32_t temp;

    if(result.type == MEMORY_MAPPING)
    {
        switch((bar_value >> 1) & 0x3)
        {

            case 0: // 32 Bit Mode
            case 1: // 20 Bit Mode
            case 2: // 64 Bit Mode
                break;
        }

    }
    else // INPUT_OUTPUT
    {
        result.address = (uint8_t*)(bar_value & ~0x3);
    }


    return result;
}


// Termina lo robado de marcelo.
