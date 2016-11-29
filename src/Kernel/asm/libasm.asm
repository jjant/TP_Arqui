GLOBAL __sti
GLOBAL __set_pic_master_asm
GLOBAL __set_pic_slave_asm
GLOBAL __irq_0_handler
GLOBAL __irq_1_handler
GLOBAL __irq_8_handler
GLOBAL __irq_11_handler

EXTERN __irq_dispatcher
EXTERN __outportb

%include "./asm/macros.m"

section .text

__irq_0_handler:
	__irq_handler 0
	
__irq_1_handler:
	__irq_handler 1

__irq_8_handler:
	__irq_handler 8

__irq_11_handler:
	__irq_slave_handler 11

__sti:
	sti
	ret
	
__set_pic_master_asm:
	push 	rbp
	mov 	rbp, rsp
	
	mov 	rax, rdi
	out 	21h, al
	call 	__outportb
	
	mov 	rsp, rbp
	leave
	ret

__set_pic_slave_asm:
	push  rbp
  mov   rbp, rsp

  mov   ax, di  ; en al esa la mascara
  out	  0A1h, al

  leave
  ret
