#ifndef __ETHERNET_H
#define __ETHERNET_H

#include <stdint.h>

#define mac_len 6

void __init_network();
void __clear_interrupt_rtl();
uint16_t __rtl_vendor_id();
uint16_t __rtl_device_id();
void __rtl_handler();
void __set_up_rtl_bus_mastering();
void rtl_send(char *, int);
uint8_t * __get_own_mac(uint8_t mac_buffer[mac_len]);

#define eth_addr_len  6
#define eth_head_len  14
#define eth_data_len  1400
#define eth_p_802_3   0x0001 // Dummy.

struct eth_header {
  unsigned char dest[eth_head_len];
  unsigned char src[eth_head_len];
  unsigned short proto;
};

typedef struct {
  struct eth_header header;
  char  data[eth_data_len];
} eth_frame;

#endif
