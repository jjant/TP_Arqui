//Fuente: http://www.scs.stanford.edu/histar/src/uinc/linux/if_ether.h

#ifndef __ETHERNET_H
#define __ETHERNET_H

/* IEEE 802.3 Ethernet magic constants. */
#define ETH_ALEN  6   /* #bytes in eth addr   */
#define ETH_HLEN  14    /* #bytes in eth header   */
#define ETH_ZLEN  60    /* min #bytes in frame    */
#define ETH_FLEN  1536    /* max #bytes in frame    */
#define ETH_DLEN  (ETH_FLEN - ETH_HLEN) /* max #bytes of data */

#define ETH_P_802_3 0x0001    /* Dummy type for 802.3 frames  */

/* Define the Ethernet Broadcast Address (48 bits set to "1"). */
#define ETH_A_BCAST     "\377\377\377\377\377\377"



#pragma pack(push)
#pragma pack(1)

/* This is an Ethernet frame header. */
struct ethhdr {
  unsigned char   dst[ETH_ALEN];  /* destination eth addr */
  unsigned char   src[ETH_ALEN];  /* source ether addr  */
  unsigned short  proto;    /* packet type ID field */
};


/* This is the complete Ethernet frame. */
typedef struct{
  struct ethhdr hdr;      /* frame header   */
  char      data[ETH_DLEN]; /* frame data (variable)*/
}  ethframe;

#pragma pack(pop)

#endif



#define __ignore_code
#ifndef __ignore_code


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
uint8_t * __get_own_mac(uint8_t *);
void __print_mac_address(uint8_t *);
void __print_own_mac();
/*
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
*/


/* IEEE 802.3 Ethernet magic constants. */
#define ETH_ALEN  6   /* #bytes in eth addr   */
#define ETH_HLEN  14    /* #bytes in eth header   */
#define ETH_ZLEN  60    /* min #bytes in frame    */
#define ETH_FLEN  1536    /* max #bytes in frame    */
#define ETH_DLEN  (ETH_FLEN - ETH_HLEN) /* max #bytes of data */

#define ETH_P_802_3 0x0001    /* Dummy type for 802.3 frames  */

/* Define the Ethernet Broadcast Address (48 bits set to "1"). */
#define ETH_A_BCAST     "\377\377\377\377\377\377"


void rtlHandler();

#pragma pack(push)
#pragma pack(1)

/* This is an Ethernet frame header. */
struct ethhdr {
  unsigned char   dst[ETH_ALEN];  /* destination eth addr */
  unsigned char   src[ETH_ALEN];  /* source ether addr  */
  unsigned short  proto;    /* packet type ID field */
};


/* This is the complete Ethernet frame. */
typedef struct{
  struct ethhdr hdr;      /* frame header   */
  char      data[ETH_DLEN]; /* frame data (variable)*/
}  ethframe;

#pragma pack(pop)
#endif

#endif
