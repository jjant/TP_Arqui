GLOBAL putc_asm

putc_asm:
	mov		rax, 0	; write syscall
	mov		rbx, rdi
	mov		rcx, 1
	int		80h
	ret
