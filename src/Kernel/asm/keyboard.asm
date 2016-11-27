GLOBAL __key_pressed_asm
GLOBAL __getchar
;__ignore_code
;  robada
GLOBAL keyRead

section .text
keyRead:
	xor rax, rax
	in al, 64h
	and al, 1 ;Me quedo con el ultimo bit
	test al, al
	jz .end
	in al, 60h
	.end:
	ret

;;;;;;;

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

__getchar:
	push 	rbp
	mov 	rbp, rsp

	xor		rax, rax	; key is ready to be read, clear rax.
	in		al, 60h
	
	leave
	ret

key_not_ready:
	mov		rax, 0h		; return 0: no key.
	leave
	ret
