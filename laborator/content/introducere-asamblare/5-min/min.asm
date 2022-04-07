%include "printf32.asm"

section .text
    global main
    extern printf

main:
    ;cele doua numere se gasesc in eax si ebx
    mov eax, 1
    mov ebx, 3
    ; TODO: aflati minimul
    mov ecx, eax
    cmp ecx, ebx
    jg swap
back:
    PRINTF32 `%d\n\x0`, eax ; afiseaza minimul
    ret

swap:
    xchg eax, ebx
    jmp back
