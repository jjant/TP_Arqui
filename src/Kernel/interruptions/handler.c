#include <handler.h>
#include <keyboard.h>
#include <video.h>
#include <ethernet.h>
#include <rtl.h>
#include <stdint.h>
#include <tick.h>

void __set_pic_slave_asm(uint8_t);
void __set_pic_slave_asm(uint8_t);

typedef void (*handler_t)(void);

handler_t handlers[30];

void __tick_handler() {
}

void __key_handler() {
  __push_key();
}

void __initialize_handlers() {
  handlers[0]  = __tick_handler;
	handlers[1]  = __key_handler;
  handlers[11] = __net_handler;
}

void __irq_dispatcher(int irq) {
	handlers[irq]();
}

void __set_pic_master(uint8_t data) {
  __set_pic_master_asm(data);
}

void __set_pic_slave(uint8_t data) {
  __set_pic_slave_asm(data);
}
