GLOBAL getchar_asm
GLOBAL set_keyboard_language

getchar_asm:
	push	rbp
	mov 	rbp, rsp

	mov 	rax, 3
	int 	80h

	leave
	ret

set_keyboard_language:
  push rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 5 ; syscall change language
  mov   rbx, rdi
  mov   rcx, 1
  int   80h

  leave
  ret

key_not_ready:
	mov		rax, 0h		; return 0: no key.
	leave
	ret