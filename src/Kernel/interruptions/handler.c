#include <handler.h>
#include <keyboard.h>
#include <video.h>
#include <ethernet.h>

typedef void (*handler_t)(void);

handler_t handlers[5];

void __tick_handler() {
}

void __key_handler() {
  __push_key();
}

void __initialize_handlers() {
  handlers[0]  = __tick_handler;
	handlers[1]  = __key_handler;
  handlers[11] = __rtl_handler;
}

void __irq_dispatcher(int irq) {
	handlers[irq]();
}

