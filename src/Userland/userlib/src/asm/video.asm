GLOBAL cls
GLOBAL set_color

cls:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 2
  int   80h

  leave
  ret

set_color:
  push rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 1
  mov   rbx, rdi
  mov   rcx, 1
  int   80h

  leave
  ret