GLOBAL __key_pressed_asm

__key_pressed_asm:
	push	rbp
	mov		rbp, rsp

	in		al, 64h
	and		al, 1h
	cmp		al, 1h
	jnz		key_not_ready
	xor		rax, rax	; key is ready to be read, clear rax.
	in		al, 60h
	leave
	ret

key_not_ready:
	mov		rax, 0h		; return 0: no key.
	leave
	ret