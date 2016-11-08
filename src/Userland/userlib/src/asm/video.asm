GLOBAL cls

cls:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 2
  int   80h

  leave
  ret