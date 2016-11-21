GLOBAL read_message_asm

read_message_asm:
  push rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 8
  int   80h

  leave
  ret