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

%macro __irq_handler 1
	pushaq
	mov 	rdi, %1
	call	__irq_dispatcher
	mov 	al, 20h ;eoi
	out 	20h, al
	popaq
	iretq
%endmacro

%macro __irq_slave_handler 1
	pushaq
	mov 	rdi, %1
	call	__irq_dispatcher
	mov 	al, 20h  ;eoi
	out 	0A0h, al ;eoi slave
	out 	20h, al  ;eoi master
	popaq
	iretq
%endmacro
