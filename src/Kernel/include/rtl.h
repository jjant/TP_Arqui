#ifndef __RTL_H
#define __RTL_H

void rtlSend();
void rtl_init();
void rtl_notify_connection(int connect);
void rtl_clear_msgs();
void rtlHandler();

int rtl_get_id();
int rtl_next_msg(char* buf, void * info, int max_size);
void rtl_send(char * msg, int dst);

int rtl_get_active_users(int * vec);

void rtlPrintMac();
void printDetails();
uint8_t nextDesc(uint8_t current);
#endif
