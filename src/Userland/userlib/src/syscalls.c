#include "syscalls.h"


#define SYS_READ 3
#define SYS_WRITE 4
#define SYS_CLRSCRN 5
#define SYS_MEMALLOC 6
#define SYS_SEND_MSG 7
#define SYS_SEND_BROADCAST 8
#define SYS_GET_MSG 9
#define SYS_CLEAR_MSGS 10
#define SYS_CONNECT 11
#define SYS_DISCONNECT 12
#define SYS_GET_ACTIVE_USERS 13
#define SYS_GETTICKS 14
#define SYS_GETRTCDATA 15
#define SYS_GET_NETWORK_ID 16

uint64_t _syscall(uint64_t code, uint64_t param1, uint64_t param2, uint64_t param3);

//System call READ
uint64_t sys_read(int fd, int * buf, int size){
  return _syscall(SYS_READ, fd, (uint64_t)buf, (uint64_t)size);
}

//System call WRITE
uint64_t sys_write(int fd, char * str, int size){
  return _syscall(SYS_WRITE, fd, (uint64_t)str, (uint64_t)size);
}

//System call para borrar la pantalla
uint64_t sys_clrscrn(){
  return _syscall(SYS_CLRSCRN, 0,0,0);
}

// Para alocar memoria
uint64_t sys_memalloc(uint64_t bytes){
  return _syscall(SYS_MEMALLOC, bytes, 0, 0);
}

// System call para enviar un mensaje a la red
uint64_t sys_send(char * msg, char user){
  return _syscall(SYS_SEND_MSG, (uint64_t)msg, user, 0);
}

uint64_t sys_broadcast(char * msg){
  return _syscall(SYS_SEND_BROADCAST, (uint64_t)msg, 0, 0);
}

//Syscall para recuperar el siguiente mensaje no leido de la cola
//Devuelve -1 si no hay mensajes, 0 si hay algo
//Se escribe en msg_info
uint64_t sys_get_msg(char * buf, msg_desc* msg_info, int max_size){
  return _syscall(SYS_GET_MSG, (uint64_t)buf, (uint64_t)msg_info, max_size);
}


//Resetea la cola de mensajes
uint64_t sys_clear_msgs(){
  return _syscall(SYS_CLEAR_MSGS, 0, 0, 0);
}

//Se conecta a la red (expone el usuario al resto de la red)
uint64_t sys_connect(){
  return _syscall(SYS_CONNECT, 0, 0, 0);
}

//Se desconecta de la red (esconde el usuario del resto de la red)
uint64_t sys_disconnect(){
  return _syscall(SYS_DISCONNECT, 0, 0, 0);
}

//Llena vec con los numeros de los usuarios activos (max 255). 
//Devuelve la cantidad que se escribio
uint64_t sys_get_active_users(int * vec){
  return _syscall(SYS_GET_ACTIVE_USERS, (uint64_t)vec, 0, 0);
}

uint64_t sys_getAmountOfTicks(){
  return _syscall(SYS_GETTICKS, 0, 0, 0);
}

uint64_t sys_get_rtc_data(int i){
  return _syscall(SYS_GETRTCDATA, i, 0, 0);
}


uint64_t sys_get_network_id(){
  return _syscall(SYS_GET_NETWORK_ID,0,0,0);
}
