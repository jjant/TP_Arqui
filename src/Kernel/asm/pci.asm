; Pure64 -- a 64-bit OS loader written in Assembly for x86-64 systems
; Copyright (C) 2008-2014 Return Infinity -- see LICENSE.TXT
;
; PCI Functions. http://wiki.osdev.org/PCI
; =============================================================================
GLOBAL __os_pci_read_reg
GLOBAL __os_pci_write_reg

section .text:
; -----------------------------------------------------------------------------
; __os_pci_read_reg -- Read a register from a PCI device
;  IN:  BL  = Bus number
; CL  = Device/Function number
; DL  = Register number
; OUT:  EAX = Register information
; All other registers preserved
; Data form is binary 10000000 bbbbbbbb dddddfff rrrrrr00
__os_pci_read_reg:
  push rdx
  push rcx
  push rbx

  shl ebx, 16     ; Move Bus to bits 23 - 16
  shl ecx, 8      ; Move Device/Function to bits 15 - 8
  mov bx, cx
  shl edx, 2      ; Move Register to bits 7 - 2
  mov bl, dl
  and ebx, 0x00ffffff   ; Clear bits 31 - 24
  or ebx, 0x80000000    ; Set bit 31
  mov eax, ebx
  mov dx, PCI_CONFIG_ADDRESS
  out dx, eax
  mov dx, PCI_CONFIG_DATA
  in eax, dx

  pop rbx
  pop rcx
  pop rdx
ret
; -----------------------------------------------------------------------------


__os_pci_write_reg:
  push rbx
  push rcx

  mov rbx, rdi
  mov rcx, rsi

  shl ebx, 16     ; Move Bus to bits 23 - 16
  shl ecx, 8      ; Move Device/Function to bits 15 - 8
  mov bx, cx
  mov bl, dl
  and ebx, 0x00ffffff   ; Clear bits 31 - 24
  or ebx, 0x80000000    ; Set bit 31
  mov eax, ebx
  mov dx, PCI_CONFIG_ADDRESS
  out dx, eax
  mov dx, PCI_CONFIG_DATA
  pop rax
  out dx, eax

  pop rbx
ret

PCI_CONFIG_ADDRESS  EQU 0x0CF8
PCI_CONFIG_DATA   EQU 0x0CFC

