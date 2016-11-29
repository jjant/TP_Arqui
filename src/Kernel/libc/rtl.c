#include <rtl.h>
#include <ports.h>
#include <string.h>
#include <lib.h>

static uint8_t MAC[6];

static struct {
  ethframe frame;
  uint32_t size;
} transmission;

typedef struct {
  char present;
  struct {
    char broadcast;
    char user;
    char data[MAX_MSG_SIZE + 1];
  } msg;
} message_t;

typedef struct {
  int broadcast;
  int user;
} message_meta_t;

static message_t message_buffer[MSG_BUF_SIZE];
static uint8_t in_buffer[BUF_SIZE] = {0};

static int pointer = 0;
static int current = 0;

static void __net_receive(int is_broadcast, uint8_t * msg);
static int __broadcasting(uint8_t *);

void __net_init(){
  int i;

  __outportb( IOADDR + 0x52, 0x0); // POWER
  __outportb( IOADDR + 0x37, 0x10); // RESET
  while( (__inportb(IOADDR + 0x37) & 0x10) != 0); // CLEAN 
  __outportdw(IOADDR + 0x30, (uint32_t)(long)in_buffer); // BUFFER IN
  __outportw(IOADDR + 0x3C, 0x000f); // TRANSMIT_OK & RECEIVE_OK SETUP
  __outportdw(IOADDR + 0x44, 0xf | (1 << 7)); // PACKAGES CLASSES SETUP
  __outportb(IOADDR + 0x37, 0x0C); // ENABLE TO TRANSMIT AND RECEIVE
  __outportdw(TSAD0, (uint32_t)(long)&transmission.frame); // SETUP BUFFER

  // MAC SETUP
  for(i = 0; i < MAC_SIZE ; i++){
    transmission.frame.hdr.src[i] = __inportb(IOADDR + i);
    MAC[i] = __inportb(IOADDR + i);
  }
}

void __net_handler() {
  uint16_t isr = __inportw(ISR);

  if (isr & RECEIVE_OK) {
    uint8_t * frame = in_buffer + RX_HEADER_SIZE;
    uint8_t valid_mac = in_buffer[ORIGIN_USER_BYTE_OFFSET] >= 0 && in_buffer[ORIGIN_USER_BYTE_OFFSET] <= 9;

    if (valid_mac) __net_receive(__broadcasting(frame), in_buffer);
  }

  __net_init();
}

static int __broadcasting(uint8_t * frame) {
  int i;
  for(i = 0; i < MAC_SIZE ; i++) if(frame[i] != 0xFF) return 0;
  return 1;
}

static void __net_receive(int is_broadcast, uint8_t * frame) { 
  if(message_buffer[current].present == TRUE) return;

  message_buffer[current].present = TRUE;
  message_buffer[current].msg.broadcast = is_broadcast;
  message_buffer[current].msg.user = frame[ORIGIN_USER_BYTE_OFFSET];
  
  strncpy(message_buffer[current].msg.data, (char *)(frame + RX_DATA_OFFSET), MAX_MSG_SIZE);
  current++;
  current = current % MSG_BUF_SIZE;
}

int __net_read(char* buf, void * info, int max_size){
  char dst_buf[5];
  if(message_buffer[pointer].present == FALSE)
    return 0;
  // KILL MESSAGES THAT ARE FOR OTHER USERS
  if( !message_buffer[pointer].msg.broadcast && message_buffer[pointer].msg.data[0] != int_to_str(MAC[5], dst_buf)[0]) {
    *buf = 0;
    pointer++;
    pointer %= MSG_BUF_SIZE;
    return 1;
  }
  // READ MESSAGE
  max_size = max_size < MAX_MSG_SIZE ? max_size : MAX_MSG_SIZE;
  char * next = message_buffer[pointer].msg.data;
  strncpy(buf, next + 1, MAX_MSG_SIZE);
  message_buffer[pointer].present = FALSE;

  // LOAD MESSAGE
  ((message_meta_t*)info)->broadcast = message_buffer[pointer].msg.broadcast;
  ((message_meta_t*)info)->user = message_buffer[pointer].msg.user;

  pointer++;
  pointer = pointer % MSG_BUF_SIZE;

  return 1;
};

void __net_clear(){
  int i;
  for(i = 0; i < MAX_MSG_SIZE; i++) {
    message_buffer[i].present = FALSE;
  }

  current = 0;
  pointer = 0;
}

int __net_id() {
  return MAC[5];
}

void __net_send(char * msg, int dst){
  char send_msg[1000];
  char dst_str[5];
  // SET DESTINATION MAC
  static unsigned char brdMAC[6] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF };
  unsigned char dstMAC[6] = { 0xBA, 0xDA, 0x55, 0xEE, 0x55, (unsigned char)dst };
  memcpy(transmission.frame.hdr.dst, dst < 0 ? brdMAC : dstMAC, 6);

  // PREPARE MESSAGE
  int_to_str(dst, dst_str);
  strcpy(send_msg, dst_str); //Prepends dst to message
  strcat(send_msg, msg);

  // PREPARE BUFFERS
  uint32_t tsd = TSD0;
  transmission.frame.hdr.proto = ETH_P_802_3;
  uint32_t descriptor = ETH_HLEN + strlen(send_msg);

  // LOAD MESSAGE

  memcpy(transmission.frame.data, send_msg, strlen(send_msg));

  transmission.size = descriptor; 
  descriptor &= ~(TSD_OWN);
  descriptor &= ~(0x3f << 16);

  // SEND  
  while (!(__inportdw(tsd) & TSD_OWN));
  __outportdw(tsd, descriptor);
}
