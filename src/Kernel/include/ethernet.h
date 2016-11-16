#ifndef __ETHERNET_H
#define __ETHERNET_H

#include <stdint.h>

void __init_network();
void __clear_interrupt_rtl();
uint16_t __rtl_vendor_id();
uint16_t __rtl_device_id();
void __rtl_handler();
void __set_up_rtl_bus_mastering();

#endif
