GLOBAL __syscall_handler
EXTERN __syscall_dispatcher

GLOBAL __int_80_with_write_syscall

__syscall_handler:
	pushaq
	mov 	rdi, rax	; syscall id
	mov 	rsi, rbx	; syscall param 1
	mov 	rdx, rcx	; syscall param 2
	call	__syscall_dispatcher
	popaq
	iretq

