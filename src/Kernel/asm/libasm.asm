GLOBAL cpuVendor
GLOBAL sti
GLOBAL __set_pic_master_asm
GLOBAL __set_pic_slave_asm
GLOBAL irq0Handler
GLOBAL irq1Handler
GLOBAL irq11Handler

EXTERN __irq_dispatcher

%include "./asm/macros.m"

section .text

irq11Handler:
	irqHandler 11

irq1Handler:
	irqHandler 1

irq0Handler:
	irqHandler 0
	
sti:
	sti
	ret
	
__set_pic_master_asm:
	push	rbp
	mov 	rbp, rsp
	
	mov 	rax, rdi
	out 	0x21, al

	leave	
	ret

;__set_pic_slave_asm(uint8_t data)
; data: RDI
__set_pic_slave_asm:
	push	rbp
	mov		rbp, rsp

	mov		rax, rdi
	out		0xA1, al

	leave
	ret

cpuVendor:
	push rbp
	mov rbp, rsp

	push rbx

	mov rax, 0
	cpuid

	mov [rdi], ebx
	mov [rdi + 4], edx
	mov [rdi + 8], ecx

	mov byte [rdi+13], 0

	mov rax, rdi

	pop rbx

	mov rsp, rbp
	pop rbp
	ret
