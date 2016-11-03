#include <handler.h>
#include <video.h>

typedef void (*handler_t)(void);

handler_t handlers[5];

void __tick_handler() {
}

void __initialize_handlers() {
	handlers[0] = __tick_handler;
}

void __irq_dispatcher(int irq) {
	handlers[irq]();
}

