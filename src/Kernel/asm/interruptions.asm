GLOBAL __int_11_asm

; void __int_asm(uint16_t interrupt)
; interrupt: RDI
__int_11_asm:
  push  rbp
  mov   rbp, rsp

  int   0x0B

  leave
  ret  
