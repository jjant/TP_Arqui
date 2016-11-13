GLOBAL __outportb_asm
GLOBAL __inportb_asm
GLOBAL __outportw_asm
GLOBAL __outportdw_asm
GLOBAL __outport64_asm
GLOBAL __inportdw_asm

__outportb_asm:
  push  rbp
  mov   rbp, rsp

  push  rdx
  push  rax

  mov   al, dil
  mov   dx, si

  out   dx, al

  pop   rax
  pop   rdx
  leave
  ret

__inportb_asm:
  push  rbp
  mov   rbp, rsp

  push  rdx

  mov   dx, di
  in    al, dx

  pop   rdx
  leave
  ret

; __outportw(uint16_t port, uint16_t data)
__outportw_asm:
  push  rbp
  mov   rbp, rsp
  push  rax
  push  rdx

  mov   rdx, rdi    
  mov   rax, rsi
  out   dx, ax

  pop   rdx
  pop   rax
  leave
  ret


;__outportdw(uint16_t port, uint32_t data)
; port: RDI
; data: RSI

__outportdw_asm:
  push  rbp
  mov   rbp, rsp
  push  rdx
  push  rax

  mov   rdx, rdi
  mov   rax, rsi
  out   dx, eax

  pop   rax
  pop   rdx
  leave
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

;__inportdw_asm(uint16_t port);
; port: RDI
__inportdw_asm:
  push  rbp
  mov   rbp, rsp
  push  rbx
  push  rax

  mov rbx, rdi
  mov rax, rsi
  mov dx, bx
  in eax, dx

  pop   rax
  pop   rbx
  leave
  ret

