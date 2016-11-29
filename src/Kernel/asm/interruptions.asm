GLOBAL __int_2B_asm

; void __int_asm(uint16_t interrupt)
; interrupt: RDI
__int_2B_asm:
  push  rbp
  mov   rbp, rsp

  int   0x2B

  leave
  ret  
