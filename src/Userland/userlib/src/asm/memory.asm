GLOBAL reserve_memory

reserve_memory:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 7 ; syscall reserve memory
  mov   rbx, rdi
  mov   rcx, 1
  int   80h

  leave
  ret