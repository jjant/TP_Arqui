
%macro pushaq 0
	push rax
	push rbx
	push rcx
	push rdx
	push rbp
	push rdi
	push rsi
	push r8
	push r9
	push r10
	push r11
	push r12
	push r13
	push r14
	push r15
%endmacro

%macro popaq 0
	pop r15
	pop r14
	pop r13
	pop r12
	pop r11
	pop r10
	pop r9
	pop r8
	pop rsi
	pop rdi
	pop rbp
	pop rdx
	pop rcx
	pop rbx
	pop rax
%endmacro


%macro irqHandler 1
	pushaq

	mov rdi, %1
	call irqDispatcher
	
	mov al, 20h ; EOI
	out 20h, al
	
	popaq

	iretq
%endmacro



%macro irqSlaveHandler 1
	pushaq

	mov rdi, %1
	call irqDispatcher
	
	mov al, 20h ; EOI

	out 0A0h, al ;EOI al PIC esclavo
	out 20h, al  ;EOI al PIC primario
	
	popaq

	iretq
%endmacro


;%macro pushaq 0
;	push rax
;	push rbx
;	push rcx
;	push rdx
;	push rbp
;	push rdi
;	push rsi
;	push r8
;	push r9
;	push r10
;	push r11
;	push r12
;	push r13
;	push r14
;	push r15
;%endmacro
;
;%macro popaq 0
;	pop r15
;	pop r14
;	pop r13
;	pop r12
;	pop r11
;	pop r10
;	pop r9
;	pop r8
;	pop rsi
;	pop rdi
;	pop rbp
;	pop rdx
;	pop rcx
;	pop rbx
;	pop rax
;%endmacro
;
;
;%macro irqHandler 1
;	pushaq
;
;	mov rdi, %1
;	call __irq_dispatcher
;	
;	mov al, 20h ; EOI
;	out 20h, al
;	
;	popaq
;
;	iretq
;%endmacro
;
;%macro irq_slave_handler 1
;	pushaq
;
;	mov	rdi, %1
;	call __irq_dispatcher
;	mov al, 20h ; EOI
;	out 0xA0, al
;	out 20h, al
;
;	popaq
;	iretq
;%endmacro
