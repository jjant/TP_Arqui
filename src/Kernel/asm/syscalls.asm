GLOBAL syscallHandler
EXTERN syscallDispatcher  

GLOBAL _write

%include "./asm/macros.m"

section .text

syscallHandler:
  pushaq

  mov rdi, rax ;Primer parametro rax (codigo)
  mov rsi, rbx ;Segundo parametro rbx (1° param syscall)

  mov rbx, rdx
  mov rdx, rcx ;Tercer parametro rcx (2°param syscall)
  mov rcx, rbx ; Cuarto parametro lo que estaba en rdx (3° param syscall)

  call syscallDispatcher

  mov [aux], rax ;valor de retorno
  
  popaq 

  mov rax, [aux]

  iretq


section .bss
  aux resq 1;
