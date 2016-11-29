#ifndef __ETHERNET_H
#define __ETHERNET_H

// ETHERNET FRAMEWORK
// SOURCE: http://www.scs.stanford.edu/histar/src/uinc/linux/if_ether.h
// BY AUGUSTO

#define ETH_ALEN  6
#define ETH_HLEN  14
#define ETH_ZLEN  60
#define ETH_FLEN  1536
#define ETH_DLEN  (ETH_FLEN - ETH_HLEN)
#define ETH_P_802_3 0x0001
#define ETH_A_BCAST     "\377\377\377\377\377\377"

#pragma pack(push)
#pragma pack(1)

struct ethhdr {
  unsigned char   dst[ETH_ALEN];
  unsigned char   src[ETH_ALEN];
  unsigned short  proto;
};

typedef struct{
  struct ethhdr hdr;
  char          data[ETH_DLEN];
} ethframe;

#pragma pack(pop)
#endif