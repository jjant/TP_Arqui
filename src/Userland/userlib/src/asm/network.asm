GLOBAL net_send
GLOBAL net_broadcast
GLOBAL net_connect
GLOBAL net_disconnect
GLOBAL net_clear
GLOBAL net_read
GLOBAL net_users
GLOBAL net_id

; net_send(char * msg, int dst)
;
net_send:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  xor   rbx, rbx
  xor   rcx, rcx
  mov   rax, 8 ; syscall send message
  mov   rbx, rdi 
  mov   rcx, rsi
  int   80h

  leave
  ret

net_broadcast:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  xor   rbx, rbx
  xor   rcx, rcx
  mov   rax, 8 ; syscall broadcast
  mov   rbx, rdi
  mov   rcx, -1
  int   80h

  leave
  ret

net_connect:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  xor   rbx, rbx
  mov   rax, 12 ; syscall connect
  mov   rbx, 1
  int   80h

  leave
  ret

net_disconnect:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  xor   rbx, rbx
  mov   rax, 12 ; syscall disconnect
  mov   rbx, 0
  int   80h

  leave
  ret

net_clear:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 10 ; syscall clear
  int   80h

  leave
  ret

net_read:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  xor   rbx, rbx
  xor   rcx, rcx
  xor   rdx, rdx
  mov   rax, 9 ; syscall read message
  mov   rbx, rdi
  mov   rcx, rsi
  mov   rcx, rsi ;como pasra el 3er param?
  int   80h

  leave
  ret

net_users:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  xor   rbx, rbx
  mov   rax, 14 ; syscall get active users
  mov   rbx, rdi
  int   80h

  leave
  ret

net_id:
  push  rbp
  mov   rbp, rsp

  xor   rax, rax
  mov   rax, 16 ; syscall get network id
  int   80h

  leave
  ret
