GLOBAL __outportb_asm
GLOBAL __outportw_asm
GLOBAL __outportdw_asm
GLOBAL __inportb_asm
GLOBAL __inportw_asm
GLOBAL __inportdw_asm

__outportb_asm:
  push  rbp
  mov   rbp, rsp

  push rbx
  push rax 

  mov rbx, rdi
  and rbx, 0xFFFF

  mov rax, rsi

  mov dx, bx
  out dx, al
  
  pop rax
  pop rbx
  leave
  ret

; __outportw(uint16_t port, uint16_t data)
__outportw_asm:
  push  rbp
  mov   rbp, rsp

  push rbx
  push rax 

  mov rbx, rdi
  and rbx, 0xFFFF

  mov rax, rsi

  mov dx, bx
  out dx, ax

  pop rax
  pop rbx
  leave
  ret


;__outportdw(uint16_t port, uint32_t data)
; port: RDI
; data: RSI

__outportdw_asm:
  push  rbp
  mov   rbp, rsp

  push rbx
  push rax 

  mov rbx, rdi
  and rbx, 0xFFFF

  mov rax, rsi

  mov dx, bx
  out dx, eax
  
  pop rax
  pop rbx
  leave
  ret

;uint8_t __inportb_asm(uint16_t port);
; port: RDI
__inportb_asm:
  push  rbp
  mov   rbp, rsp

  push rbx

  mov rbx, rdi
  and rbx, 0xFFFF

  mov rax, rsi

  mov dx, bx
  in al, dx
  and rax, 0xff;
  
  pop rbx
  leave
  ret

;uint16_t __inportw_asm(uint16_t port);
; port: RDI
__inportw_asm:
  push  rbp
  mov   rbp, rsp

  push rbx

  mov rbx, rdi
  and rbx, 0xFFFF

  mov rax, rsi

  mov dx, bx
  in ax, dx
  and rax, 0xffff;
  
  pop rbx
  leave
  ret

;uint32_t __inportdw_asm(uint16_t port);
; port: RDI
__inportdw_asm:
  push  rbp
  mov   rbp, rsp

  push rbx

  mov rbx, rdi
  and rbx, 0xFFFF

  mov rax, rsi

  mov dx, bx
  in eax, dx

  pop rbx
  leave
  ret
