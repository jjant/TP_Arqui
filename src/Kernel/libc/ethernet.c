#include <ethernet.h>
#include <ports.h>
#include <stdint.h>
#include <memory.h>
#include <pci.h>

#define ioaddr        0xC000
#define cmd_reg       0x37
#define rbstart_reg   0x30
#define config_1_reg  0x52
#define imr_reg       0x3C
#define isr_reg       0x3E

#define rtl_vendor_id 0x10EC
#define rtl_device_id 0x8139
#define rtl_interrupt 0x0B;

static void __reset();
static void __turn_on_rtl();
static void __set_up_buffer();
static void __set_up_imr();
static void __promiscuous_rtl();
static void __enable_receive_transmit();

static void * rx_buffer;

void __init_network() {
  __set_up_rtl_bus_mastering();
  __turn_on_rtl();
  __reset();
  rx_buffer = __malloc(900);
  __set_up_buffer(rx_buffer);
  __promiscuous_rtl();
  __enable_receive_transmit();
}

static void __turn_on_rtl() {
  __outportb(ioaddr + config_1_reg, 0x0);
}

static void __reset() {
	__outportb(ioaddr + cmd_reg, 0x10);
	//while( (__inportb(cmd_reg) & 0x10) != 0);
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
  __puts("Me llego algo\n");
  
  __clear_interrupt_rtl();
}

uint16_t __rtl_vendor_id() {
  return rtl_vendor_id;
}

uint16_t __rtl_device_id() {
  return rtl_device_id;
}

void __set_up_rtl_bus_mastering() {
  PCI_Descriptor_t rtl_descriptor = __get_rtl_descriptor();
  //WTF WHY DOES THE FIRST DIGIT NOT WORK??? THIS RETURNS 0x07 ON THE REGISTER.
  __pci_write(rtl_descriptor->bus, rtl_descriptor->device, rtl_descriptor->function, 0x04, 0x7);

/*
15  14  13  12  11      10              9           8        
|----RESERVED-----||int disable||fast b2b enab||SERR# enable|

     7           6           5             4      
|RESERVED||parity error||vga palette||memory write|

     3           2            1           0
|spec. cyc||bus master||memory space||I/O space|

15  14  13  12  11  10  9  8  7  6  5  4  3  2  1  0
 0   0   0   0   0   0  0  0  0  0  0  1  0  1  1  1
--------------  ------------  ----------  -----------
      0               0            1           7 
Interrupt Disable:
If set to 1 the assertion of the devices INTx# signal is disabled; otherwise, assertion of the signal is enabled.
Fast Back-Back Enable:
If set to 1 indicates a device is allowed to generate fast back-to-back transactions; otherwise, fast back-to-back transactions are only allowed to the same agent.
SERR# Enable:
If set to 1 the SERR# driver is enabled; otherwise, the driver is disabled.
Bit 7:
As of revision 3.0 of the PCI local bus specification this bit is hardwired to 0. In earlier versions of the specification this bit was used by devices and may have been hardwired to 0, 1, or implemented as a read/write bit.
Parity Error Response:
If set to 1 the device will take its normal action when a parity error is detected; otherwise, when an error is detected, the device will set bit 15 of the Status register (Detected Parity Error Status Bit), but will not assert the PERR# (Parity Error) pin and will continue operation as normal.
VGA Palette Snoop:
If set to 1 the device does not respond to palette register writes and will snoop the data; otherwise, the device will trate palette write accesses like all other accesses.
Memory Write and Invalidate Enable:
If set to 1 the device can generate the Memory Write and Invalidate command; otherwise, the Memory Write command must be used.
Special Cycles:
If set to 1 the device can monitor Special Cycle operations; otherwise, the device will ignore them.
Bus Master:
If set to 1 the device can behave as a bus master; otherwise, the device can not generate PCI accesses.
Memory Space:
If set to 1 the device can respond to Memory Space accesses; otherwise, the device's response is disabled.
I/O Space:
If set to 1 the device can respond to I/O Space accesses; otherwise, the device's response is disabled.
*/
}
