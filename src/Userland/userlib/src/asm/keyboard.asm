GLOBAL getchar_asm

getchar_asm:
	push	rbp
	mov 	rbp, rsp

	mov 	rax, 3
	int 	80h

	leave
	ret

key_not_ready:
	mov		rax, 0h		; return 0: no key.
	leave
	ret