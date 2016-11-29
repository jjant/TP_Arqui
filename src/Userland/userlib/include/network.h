#ifndef NETWORK_H
#define NETWORK_H

#include <stdint.h>

uint64_t net_read(char *, void *, uint64_t);
void net_send(char *, uint8_t);
void net_broadcast(char *);
void net_clear();
void net_connect();
void net_disconnect();
uint64_t net_users(int *);
uint64_t net_id();

#endif