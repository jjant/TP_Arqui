GLOBAL read_message_asm
GLOBAL send_message

read_message_asm:
  push rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 8
  int   80h

  leave
  ret

send_message:
  push rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 9 ; syscall send message
  mov   rbx, rdi
  mov   rcx, rsi
  int   80h

  leave
  ret