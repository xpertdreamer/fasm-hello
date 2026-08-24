format ELF64

public compute

define GATE_AND 0
define GATE_OR  1
define GATE_NOT 2

define MASK 1
  
section '.text' executable
compute:
  mov al, [rsi]
  mov bl, [rsi+1]

  cmp dil, GATE_AND
  je _and
  cmp dil, GATE_OR
  je _or
  cmp dil, GATE_NOT
  je _not

  mov al, 0
  ret

_and:
  and al, bl
  ret

_or:
  or al, bl
  ret

_not:
  not al
  and al, MASK
  ret
