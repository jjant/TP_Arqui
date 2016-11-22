GLOBAL __outportb_asm
GLOBAL __inportb_asm
GLOBAL __outportw_asm
GLOBAL __outportdw_asm
GLOBAL __outport64_asm
GLOBAL __inportw_asm
GLOBAL __inportdw_asm

__outportb_asm:
  push rbx
  push rax 

  mov rbx, rdi
  and rbx, 0xFFFF ;16 bits

  mov rax, rsi

  mov dx, bx
  out dx, al
  

  pop rax
  pop rbx
  ret

; __outportw(uint16_t port, uint16_t data)
__outportw_asm:
  push rbx
  push rax 

  mov rbx, rdi
  and rbx, 0xFFFF ;16 bits

  mov rax, rsi

  mov dx, bx
  out dx, ax
  

  pop rax
  pop rbx
  ret


;__outportdw(uint16_t port, uint32_t data)
; port: RDI
; data: RSI

__outportdw_asm:
  push rbx
  push rax 

  mov rbx, rdi
  and rbx, 0xFFFF ;16 bits

  mov rax, rsi

  mov dx, bx
  out dx, eax
  

  pop rax
  pop rbx
  ret


;__outport64(uint16_t port, uint64_t data)
; port: RDI
; data: RSI

__outport64_asm:
;  push  rbp
;  mov   rbp, rsp
;  push  rdx
;  push  rax
;
;  mov   rdx, rdi
;  mov   rax, rsi
;  out   dx, rax
;
;  pop   rax
;  pop   rdx
;  leave
  ret


;uint8_t __inportb_asm(uint16_t port);
; port: RDI
__inportb_asm:
  push rbx

  mov rbx, rdi
  and rbx, 0xFFFF ;16 bits

  mov rax, rsi

  mov dx, bx
  in al, dx
  and rax, 0xff;
  
  pop rbx

  ret

;uint16_t __inportw_asm(uint16_t port);
; port: RDI
__inportw_asm:
  push rbx

  mov rbx, rdi
  and rbx, 0xFFFF ;16 bits

  mov rax, rsi

  mov dx, bx
  in ax, dx
  and rax, 0xffff;
  
  pop rbx

  ret

;uint32_t __inportdw_asm(uint16_t port);
; port: RDI
__inportdw_asm:
  push rbx

  mov rbx, rdi
  and rbx, 0xFFFF ;16 bits

  mov rax, rsi

  mov dx, bx
  in eax, dx

  pop rbx

  ret
