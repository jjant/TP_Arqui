#ifndef __RTL_H
#define __RTL_H

#include <port.h>
#include <stdint.h>
#include <string.h>
#include <memory.h>
#include <ethernet.h>

// PIC
#define IOADDR 0xC000

// RTL BUFFERS
#define TSAD0 (IOADDR + 0x20)
#define TSD0 (IOADDR + 0x10)
#define TSD_OWN (1 << 13)
#define ISR (IOADDR + 0x3E) 


// RTL STATES
#define TRANSMIT_OK (1 << 2)
#define RECEIVE_OK   1
#define ISR_ERROR   (1<<1 | 1<<3)

// MISCELANEOUS
#define MAC_SIZE 6
#define MSG_BUF_SIZE 100
#define BUF_SIZE 1000
#define MAX_MSG_SIZE 512
#define TRUE 1
#define FALSE 0

// OFFSETS
#define RX_HEADER_SIZE 4
#define RX_DATA_OFFSET (RX_HEADER_SIZE + ETH_HLEN) //Aca arranca la data posta en el frame ethernet 
#define ORIGIN_USER_BYTE_OFFSET (RX_HEADER_SIZE + MAC_SIZE + MAC_SIZE - 1)
#define TO_USER_BYTE_OFFSET (RX_HEADER_SIZE + MAC_SIZE - 1)

void __net_init();
void __net_handler();
int __net_read(char* buf, void * info, int max_size);
void __net_send(char * msg, int dst);
void __net_clear();
int __net_id();

#endif
