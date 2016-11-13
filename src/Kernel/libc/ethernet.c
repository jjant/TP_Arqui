#include <ethernet.h>
#include <ports.h>
#include <stdint.h>
#include <memory.h>

#define ioaddr        0xC000
#define cmd_reg       0x37
#define rbstart_reg   0x30
#define config_1_reg  0x52
#define imr_reg       0x3C
#define isr_reg       0x3E

static void __reset();
static void __turn_on_rtl();
static void __set_up_buffer();
static void __set_up_imr();
static void __promiscuous_rtl();
static void __enable_receive_transmit();

static void * rx_buffer;

void __init_network() {
  __turn_on_rtl();
  __reset();
  rx_buffer = __malloc(9000);
  __set_up_buffer(rx_buffer);
  __promiscuous_rtl();
  __enable_receive_transmit();
}

static void __turn_on_rtl() {
  __outportb(ioaddr + config_1_reg, 0x0);
}

static void __reset() {
	__outportb(ioaddr + cmd_reg, 0x10);
	while( (__inportb(cmd_reg) & 0x10) != 0);
}

static void __set_up_buffer(void * buffer) {
  //change later
  __outportdw(ioaddr + rbstart_reg, buffer);
}

// Only allows Transmit OK and Receive OK interrups.
static void __set_up_imr() {
  __outportw(ioaddr + imr_reg, 0x0005);
}


// check ths later
static void __promiscuous_rtl() {
  __outportdw(ioaddr + 0x44, 0xf | (1 << 7)); // (1 << 7) is the WRAP bit, 0xf is AB+AM+APM+AAP
}

// Sets the Receiver enabled (RE) and Transmitter enabled (TE) bits on.
static void __enable_receive_transmit() {
  __outportb(ioaddr + cmd_reg, 0x0C);
}

// Should be called after handling an rtl interrupt.
void __clear_interrupt_rtl() {
  __outportw(ioaddr + isr_reg, 0x1);
}

void __rtl_handler() {
  /* Do stuff */


  __clear_interrupt_rtl();
}
