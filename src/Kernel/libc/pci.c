#include <pci.h>

static void __device_power(uint8_t bus, uint8_t device) {
  uint32_t reg = __os_pci_read_reg(bus, device, 0x04);
  reg |= ( 1 << 2);
  __os_pci_write_reg(bus, device, 0x04, reg);
}

void __DMA_init(){
  __device_power(0, 0x18);
}
