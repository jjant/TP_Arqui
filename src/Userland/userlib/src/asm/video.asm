GLOBAL cls
GLOBAL set_color
GLOBAL private_line

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


private_line:
  push rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 6
  mov   rbx, rdi
  mov   rcx, 1
  int   80h

  leave
  ret