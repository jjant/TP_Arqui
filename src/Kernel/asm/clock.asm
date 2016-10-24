GLOBAL __system_seconds_asm
GLOBAL __system_minutes_asm
GLOBAL __system_hours_asm

__system_seconds_asm:
	push	rbp
	mov		rbp, rsp

	mov		rax, 0 
	out 	70h, al		; READ/WRITE seconds
	in		ax, 71h		; Copy seconds into ax

	leave
	ret

__system_minutes_asm:
	push	rbp
	mov		rbp, rsp

	mov		al, 2h					
	out 	70h, al		; READ/WRITE minutes
	in		ax, 71h

	leave
	ret

__system_hours_asm:
	push	rbp
	mov		rbp, rsp

	mov		al, 4h
	out 	70h, al		; READ/WRITE hours
	in		ax, 71h

	leave
	ret
