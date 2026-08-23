format ELF64
public _start

macro print str, size {
  mov eax, 1
  mov rdi, 1
  mov rsi, str
  mov rdx, size
  syscall
}

macro exit {
  mov eax, 60
  xor edi, edi
  syscall
}

section '.text' executable

_start:
  print msg, msg_s
  exit

section '.data' writeable
  msg db "Hello, World!", 0x0A
  msg_s = $-msg
